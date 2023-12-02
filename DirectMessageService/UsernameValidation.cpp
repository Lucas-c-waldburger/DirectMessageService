#include "UsernameValidation.h"


UsernameValidation::VChecks::ValidLenCheck::ValidLenCheck() : Validation::ValidationCheck<UserSet>(false)
{}

UsernameValidation::VChecks::ValidLenCheck::~ValidLenCheck()
{}

std::string_view UsernameValidation::VChecks::ValidLenCheck::vcFunc(std::string_view usrnm, UserSet* none = nullptr)
{
	return (usrnm.length() >= Constraints::MIN_USRNM_LEN && usrnm.length() <= Constraints::MAX_USRNM_LEN) ?
		Validation::NULL_VIEW : VCMsg::ValidLen::failMsg;
}


UsernameValidation::VChecks::LegalCharsCheck::LegalCharsCheck() : Validation::ValidationCheck<UserSet>(false)
{}

UsernameValidation::VChecks::LegalCharsCheck::~LegalCharsCheck()
{}

std::string_view UsernameValidation::VChecks::LegalCharsCheck::vcFunc(std::string_view usrnm, UserSet* none = nullptr)
{
	return (usrnm.find_first_of(Constraints::ILLEGAL_CHARS) == std::string::npos) ?
		Validation::NULL_VIEW : VCMsg::LegalChars::failMsg;
}


UsernameValidation::VChecks::UniqueUsernameCheck::UniqueUsernameCheck() : Validation::ValidationCheck<UserSet>(true)
{}

UsernameValidation::VChecks::UniqueUsernameCheck::~UniqueUsernameCheck()
{}

std::string_view UsernameValidation::VChecks::UniqueUsernameCheck::vcFunc(std::string_view usrnm, UserSet* users)
{
	return ((*users)[std::string{usrnm}] == nullptr) ? // TODO: make []overload in userSet to accept string_view?
		Validation::NULL_VIEW : VCMsg::UniqueUsername::failMsg;
}


UsernameValidation::UsernameValidator::UsernameValidator(UserSet& users)
	: Validator<UserSet>(users, { &VChecks::validLen, &VChecks::legalChars, &VChecks::uniqueUsername })
{}
