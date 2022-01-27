
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef DELEGATE_DOUBLE_LINKED_LIST_HPP
#define DELEGATE_DOUBLE_LINKED_LIST_HPP

#include<assert.h>
#include<utility>

namespace Game
{
    namespace Common
    {
        class Delegate {
        private:
            using InstancePtr = void*;
            using InternalFunction = void (*)(InstancePtr, int);

            template<void (*Function)(int)>
            static void freeFunction(InstancePtr, int arg0)
            {
                return (Function)(arg0);
            }

            template<class T, void (T::*Function)(int)>
            static void memberFunction(InstancePtr ins, int arg0)
            {
                return (static_cast<T*>(ins)->*Function)(arg0);
            }

        public:
            Delegate()
                : store_{ nullptr, nullptr } {}

            template<void (*Function)(int)>
            void bind()
            {
                store_.first = nullptr;
                store_.second = &freeFunction<Function>;
            }

            template<class T, void (T::*Function)(int)>
            void bind(T* instance)
            {
                store_.first = instance;
                store_.second = &memberFunction<T, Function>;
            }

            void invoke(int arg0) const
            {
                assert(store_.second != nullptr);
                return store_.second(store_.first, arg0);
            }

        private:
            std::pair<InstancePtr, InternalFunction> store_;
        };




        template<class Enum>
        class SubjectEnum;

        template<class Enum>
        class ObserverEnum {
        public:
            using Function = void(Enum);

            friend SubjectEnum<Enum>;

        public:
            ObserverEnum(Function* f) noexcept
                :
                func_{ f },
                prev_{ nullptr },
                next_{ nullptr }
            {
                assert(func_ != nullptr);
            }

            ObserverEnum(const ObserverEnum&) = delete;
            ObserverEnum& operator=(const ObserverEnum&) = delete;

            ~ObserverEnum() noexcept {}

            void onNotify(Enum e) noexcept {
                func_(e);
            }

        private:
            Function*       func_;
            ObserverEnum*   prev_;
            ObserverEnum*   next_;
        };

        template<class Enum>
        class SubjectEnum {
        public:
            SubjectEnum() noexcept
                : head_{ dummy }
            {
                head_.prev_ = head_.next_ = &head_;
            }

            SubjectEnum(const SubjectEnum&) = delete;
            SubjectEnum& operator=(const SubjectEnum&) = delete;

            ~SubjectEnum() noexcept {}

            void addObserver(ObserverEnum<Enum>* obs) noexcept;

            void removeObserver(ObserverEnum<Enum>* obs) noexcept;

            void notify(Enum e) noexcept;

        private:
            static void dummy(Enum e) noexcept {}

        private:
            ObserverEnum<Enum> head_;
        };

        ///------------------------------------------------------------------------------------------------

        template<class Enum>
        inline void SubjectEnum<Enum>::addObserver(ObserverEnum<Enum>* obs) noexcept
        {
            obs->next_ = head_.next_;
            head_.next_->prev_ = obs;
            head_.next_ = obs;
            obs->prev_ = &head_;
        }

        template<class Enum>
        inline void SubjectEnum<Enum>::removeObserver(ObserverEnum<Enum>* obs) noexcept
        {
            obs->prev_->next_ = obs->next_;
            obs->next_->prev_ = obs->prev_;
        }

        template<class Enum>
        inline void SubjectEnum<Enum>::notify(Enum e) noexcept
        {
            auto* current = head_.next_;
            while (current != &head_) {
                current->onNotify(e);
                current = current->next_;
            }
        }

    }
}

#endif // !DELEGATE_DOUBLE_LINKED_LIST_HPP
