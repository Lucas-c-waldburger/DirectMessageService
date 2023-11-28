#pragma once
#include <iostream>
#include <vector>
#include <string_view>

namespace Validation
{
    template <typename T>
    using VCFunc = bool(*)(T);

    //// REF OBJ-DEPENDANT VFUNC WRAPPER (BASE) ////

    template <typename REF_OBJ, typename T>
    struct RefDependantVFunc
    {
        RefDependantVFunc(REF_OBJ& ro);
        virtual ~RefDependantVFunc();

        virtual bool vf(T arg) = 0;

    protected:
        REF_OBJ& refObj;
    };




    //// VCHECK DECL ////

    template <typename T>
    struct VCheck
    {
        VCheck(VCFunc<T> vcf, const std::string& fMsg);

        const std::string& getFailMsg() const;
        bool operator()(T arg);

    private:
        VCFunc<T> vcFunc;
        std::string failMsg;
    };


    //// VALIDATOR DECL ////

    template <typename T>
    class Validator
    {
    public:
        Validator() = default;
        Validator(std::initializer_list<VCheck<T>> vcs);

        bool operator()(T arg);
        void addVCheck(VCheck<T> vc);
        const std::string& getLastFailMsg() const;

    private:
        std::vector<VCheck<T>> validationChecks;
        std::string lastFailMsg;
    };


    //// VALIDATOR TYPEDEFS ////

    using UsernameValidator = Validator<std::string_view>;



    //// VCHECK DEFS ////

    template<typename T>
    inline VCheck<T>::VCheck(VCFunc<T> vcf, const std::string& fMsg) : vcFunc(vcf), failMsg(fMsg)
    {}

    template<typename T>
    inline const std::string& VCheck<T>::getFailMsg() const
    {
        return failMsg;
    }

    template<typename T>
    inline bool VCheck<T>::operator()(T arg)
    {
        return vcFunc(arg);
    }


    //// REF-DEPENDANT VFUNC DEFS ////

    template<typename REF_OBJ, typename T>
    inline RefDependantVFunc<REF_OBJ, T>::RefDependantVFunc(REF_OBJ& ro) : refObj(ro)
    {}

    template<typename REF_OBJ, typename T>
    inline RefDependantVFunc<REF_OBJ, T>::~RefDependantVFunc()
    {}


    //// VALIDATOR DEFS ////

    template<typename T>
    inline Validator<T>::Validator(std::initializer_list<VCheck<T>> vcs)
    {
        for (auto& vc : vcs)
            validationChecks.push_back(vc);
    }

    template<typename T>
    inline bool Validator<T>::operator()(T arg)
    {
        for (auto& vc : validationChecks)
        {
            if (!vc(arg))
            {
                lastFailMsg = vc.getFailMsg();
                return false;
            }
        }
        return true;
    }

    template<typename T>
    inline void Validator<T>::addVCheck(VCheck<T> vc)
    {
        validationChecks.push_back(vc);
    }

    template<typename T>
    inline const std::string& Validator<T>::getLastFailMsg() const
    {
        return lastFailMsg;
    }



};

