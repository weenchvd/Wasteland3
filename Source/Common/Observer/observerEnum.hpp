
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include<assert.h>

namespace Game
{
    namespace Common
    {
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

        /*
        template<class Enum>
        class ObserverEnum {
        public:
            using Function = void(Enum);

            friend class SubjectEnum<Enum>;

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
                : head_{ nullptr } {}

            SubjectEnum(const SubjectEnum&) = delete;
            SubjectEnum& operator=(const SubjectEnum&) = delete;

            ~SubjectEnum() noexcept {}

            void addObserver(ObserverEnum<Enum>* obs) noexcept;

            void removeObserver(ObserverEnum<Enum>* obs) noexcept;

            void notify(Enum e) noexcept;

        private:
            ObserverEnum<Enum>* head_;
        };

        ///------------------------------------------------------------------------------------------------

        template<class Enum>
        inline void SubjectEnum<Enum>::addObserver(ObserverEnum<Enum>* obs) noexcept
        {
            obs->prev_ = nullptr;
            obs->next_ = head_;
            if (head_ != nullptr) {
                head_->prev_ = obs;
            }
            head_ = obs;
        }

        template<class Enum>
        inline void SubjectEnum<Enum>::removeObserver(ObserverEnum<Enum>* obs) noexcept
        {
            if (obs->prev_ != nullptr) {
                obs->prev_->next_ = obs->next_;
            }
            else {
                head_ = obs->next_;
            }
            if (obs->next_ != nullptr) {
                obs->next_->prev_ = obs->prev_;
            }
            obs->prev_ = obs->next_ = nullptr;
        }

        template<class Enum>
        inline void SubjectEnum<Enum>::notify(Enum e) noexcept
        {
            auto* current = head_;
            while (current != nullptr) {
                current->onNotify(e);
                current = current->next_;
            }
        }
        */

    }
}

#endif // !OBSERVER_HPP
