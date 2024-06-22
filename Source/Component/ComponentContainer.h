#pragma once

#include "RuntimeComponentContainer.h"
#include "StaticComponentContainer.h"
#include "../Util/Util.h"

namespace claw::components {
    template<class... TStaticComponents>
    class ComponentContainer
    {
    public:
        ComponentContainer() = default;
        
        template<class T>
        T& GetComponent()
        {
            if constexpr (util::is_in_pack<T, TStaticComponents...>::value)
            {
                return m_staticComponents.template GetComponent<T>();
            }
            else
            {
                return m_runtimeComponents.GetComponent<T>();
            }
        }

        template<class T, class... TArgs>
        T& AddComponent(TArgs... args)
        {
            return m_runtimeComponents.AddComponent<T>(args...);
        }

        template<class T>
        void RemoveComponent()
        {
            m_runtimeComponents.RemoveComponent<T>();
        }
        
    private:
        StaticComponentContainer<TStaticComponents...> m_staticComponents{};
        RuntimeComponentContainer m_runtimeComponents{};
    };
}
