#pragma once
#include <type_traits>

#include "IComponent.h"

namespace claw::components
{
    template<class T>
    class ComponentProvider
    {
    protected:
        ComponentProvider() = default;
        
        static_assert(std::is_base_of_v<IComponent, T>, "T must be an IComponent");
        T& GetComponent() { return t; }
    private:
        T t{};
    };

    template<class... TStaticComponents>
    class StaticComponentContainer : ComponentProvider<TStaticComponents>...
    {
        public:
        StaticComponentContainer() = default;
    
        template<class T>
        T& GetComponent()
        {
            return ComponentProvider<T>::GetComponent();
        }
    };

}
