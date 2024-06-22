#pragma once

#include <unordered_map>
#include <typeindex>
#include <memory>

#include "IComponent.h"
#include "../Util/RuntimeException.h"

namespace claw::components
{
    class RuntimeComponentContainer
    {
    public:
        RuntimeComponentContainer() = default;
    
        template<class T>
        T& GetComponent()
        {
            if (const auto& ptr = m_map[typeid(T)].get())
            {
                return *reinterpret_cast<T*>(ptr);
            }
            throw util::RuntimeException(*this, "Failed to find component " + std::string(typeid(T).name()));
        }

        template<class T, class... TArgs>
        T& AddComponent(TArgs... args)
        {
            auto pT = std::make_shared<T>(args...);
            m_map[typeid(T)] = pT;
            return *pT;
        }

        template<class T>
        void RemoveComponent()
        {
            m_map.erase(typeid(T));
        }

    private:
        std::unordered_map<std::type_index, std::shared_ptr<IComponent>> m_map{};
    };    
}
