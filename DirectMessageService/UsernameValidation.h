#pragma once
#include "UserSet.h"
#include "Validation.h"

namespace UsernameValidation
{
    namespace Constraints
    {
        static constexpr unsigned MIN_USRNM_LEN = 4;
        static constexpr unsigned MAX_USRNM_LEN = 20;
        static constexpr std::string_view ILLEGAL_CHARS = "/ &=,'-+<>[]():";
    }

    namespace VCMsg
    {
        using namespace Constraints;

        class ValidLen
        {
            static constexpr std::string_view m1 = "Username must be between ";
            static constexpr std::string_view m2 = NumToStr<signed, MIN_USRNM_LEN>::value;
            static constexpr std::string_view m3 = " and ";
            static constexpr std::string_view m4 = NumToStr<signed, MAX_USRNM_LEN>::value;
            static constexpr std::string_view m5 = " characters";
        public:
            static constexpr std::string_view failMsg = joinViews<m1, m2, m3, m4, m5>;
        };

        class LegalChars
        {
            static constexpr std::string_view m1 = "Username cannot contain the characters ";

        public:
            static constexpr std::string_view failMsg = joinViews<m1, ILLEGAL_CHARS>;
        };

        class UniqueUsername
        {
        public:
            static constexpr std::string_view failMsg = "A user with that name is already connected";
        };
    }

    using namespace Validation;

    class VChecks
    {
    private:
        class ValidLenCheck : public ValidationCheck<UserSet>
        {
        public:
            ValidLenCheck();
            virtual ~ValidLenCheck();

        private:
            std::string_view vcFunc(std::string_view usrnm, UserSet*) override;
        };

        class LegalCharsCheck : public ValidationCheck<UserSet>
        {
        public:
            LegalCharsCheck();
            virtual ~LegalCharsCheck();

        private:
            std::string_view vcFunc(std::string_view usrnm, UserSet*) override;
        };

        class UniqueUsernameCheck : public ValidationCheck<UserSet>
        {
        public:
            UniqueUsernameCheck();
            virtual ~UniqueUsernameCheck();

        private:
            std::string_view vcFunc(std::string_view usrnm, UserSet* users) override;
        };

    public:
        static inline ValidLenCheck validLen{};
        static inline LegalCharsCheck legalChars{};
        static inline UniqueUsernameCheck uniqueUsername{};
    };


    class UsernameValidator : public Validator<UserSet>
    {
    public:
        UsernameValidator(UserSet& users);
        ~UsernameValidator() = default;



    private:

    };

}


