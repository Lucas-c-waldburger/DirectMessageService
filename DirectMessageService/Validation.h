#pragma once
#include <string_view>
#include <stdexcept>
#include <vector>

namespace Validation
{
    // derived classes job to override checkUsrnm and utilize the objPtr taken in by parent
    template <typename REF_OBJ>
    class ValidationCheck
    {
    public:
        ValidationCheck(bool needRO) : needsRefObj(needRO) {};
        virtual ~ValidationCheck() {};

        const bool needsRefObj;
        std::string_view operator()(std::string_view svIn, REF_OBJ* pObj) { return vcFuncExWrapper(svIn, pObj); }

    protected:
        virtual std::string_view vcFunc(std::string_view svIn, REF_OBJ* pObj) = 0; // will return a pre-constructed fail message or NULL_VIEW
        std::string_view vcFuncExWrapper(std::string_view svIn, REF_OBJ* pObj) // ensures we don't get screwed by a null exception from mishandled default constructor args
        {
            if (needsRefObj && !pObj)
                throw std::logic_error("function requires pointer to an existing object, found nullptr instead");

            return vcFunc(svIn, pObj);
        }
    };


    // NULL_VIEW exists as a substitute for false
    static constexpr std::string_view NULL_VIEW = "";
    inline bool success(std::string_view sv) { return sv == NULL_VIEW; }

    // validator accepts variable number of constexpr vcheck-derived class instances
    // that either rely on the same object to perform their function, or don't rely on any object at all
    // validator holds a pointer to the needed object and seeds vchecks with it when called 
    // depending on their "needsRefObj" member bool
    template <typename REF_OBJ>
    class Validator
    {
    public:
        Validator(REF_OBJ& refObj, std::initializer_list<ValidationCheck<REF_OBJ>*> vcs) : objPtr(&refObj)
        {
            for (auto& vc : vcs)
                vChecks.push_back(vc);
        }
        
        virtual ~Validator() {};
        

        std::string_view operator()(std::string_view svIn)
        {
            for (auto& vc : vChecks)
            {
                std::string_view retMsg = (vc->needsRefObj) ? (*vc)(svIn, objPtr) : (*vc)(svIn, nullptr);

                if (retMsg != NULL_VIEW)
                    return retMsg;
            }

            return NULL_VIEW;
        }

    protected:
        REF_OBJ* objPtr;
        std::vector<ValidationCheck<REF_OBJ>*> vChecks; // non-owning pointers
    };
}
