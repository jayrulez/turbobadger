// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#ifndef TB_OBJECT_H
#define TB_OBJECT_H

#include "tb_core.h"
#include "tb_linklist.h"

namespace tb {

using TB_TYPE_ID = size_t;
#define TB_INVALID_TYPE_ID 0

class TB_API TypeRegistry {
public:
    static TypeRegistry& Instance() {
        static TypeRegistry instance;
        return instance;
    }

    // Register a type and return its unique ID
    TB_TYPE_ID RegisterType(const char* type_name) {
        // Check if the type is already registered
        for (auto* node = m_nodes.GetFirst(); node != nullptr; node = node->GetNext()) {
            if (strcmp(node->m_type_name, type_name) == 0) {
                return node->m_type_id; // Return existing ID
            }
        }

        // Register a new type
        TB_TYPE_ID new_id = ++m_counter;
        auto* new_node = new TypeRegistryNode(type_name, new_id);
        m_nodes.AddLast(new_node);
        return new_id;
    }

    // Get the unique ID of a type (must have been registered before)
    TB_TYPE_ID GetTypeId(const char* type_name) const {
        for (auto* node = m_nodes.GetFirst(); node != nullptr; node = node->GetNext()) {
            if (strcmp(node->m_type_name, type_name) == 0) {
                return node->m_type_id;
            }
        }
        return InvalidTypeId();  // Not registered
    }

    static TB_TYPE_ID InvalidTypeId() {
        return static_cast<TB_TYPE_ID>(0);
    }

private:
    struct TypeRegistryNode : public TBLinkOf<TypeRegistryNode> {
        const char* m_type_name;  // Type name (must have static lifetime)
        TB_TYPE_ID m_type_id;     // Unique ID for the type

        TypeRegistryNode(const char* name, TB_TYPE_ID id)
            : m_type_name(name), m_type_id(id) {}
    };

    TBLinkListAutoDeleteOf<TypeRegistryNode> m_nodes;  // Dynamically managed list of type nodes
    TB_TYPE_ID m_counter = 0;  // Counter for generating unique type IDs

    TypeRegistry() = default;
    ~TypeRegistry() = default;

    // Prevent copying or moving
    TypeRegistry(const TypeRegistry&) = delete;
    TypeRegistry(TypeRegistry&&) = delete;
    TypeRegistry& operator=(const TypeRegistry&) = delete;
    TypeRegistry& operator=(TypeRegistry&&) = delete;
};

/*  TBTypedObject implements custom RTTI so we can get type safe casts,
	and the class name at runtime.

	Each subclass is expected to define TBOBJECT_SUBCLASS to get the
	necessary implementations, instead of implementing those manually. */
class TB_API TBTypedObject
{
public:
	virtual ~TBTypedObject() {}

	/** A static template method that returns a unique id for each type. */
	template<class T> static TB_TYPE_ID GetTypeId() { static const TB_TYPE_ID id = TypeRegistry::Instance().RegisterType(GetTypeName<T>()); return id; }

	/** Returns true if the class or the base class matches the type id */
	virtual bool IsOfTypeId(const TB_TYPE_ID type_id) const { return type_id == GetTypeId<TBTypedObject>(); }

	/** Returns this object as the given type or nullptr if it's not that type. */
	template<class T> T *SafeCastTo() const { return IsOfTypeId(GetTypeId<T>()) ? const_cast<T*>(static_cast<const T*>(this)) : nullptr; }

	/** Return true if this object can safely be casted to the given type. */
	template<class T> bool IsOfType() const { return SafeCastTo<T>() != nullptr; }

	/** Get the classname of the object. */
	virtual const char *GetClassName() const { return "TBTypedObject"; }

	static const char* TypeName() { return "TBTypedObject"; }

private:
	template <typename T>
	static const char* GetTypeName() {
		return T::TypeName();
	}
};

/** Returns the given object as the given type, or nullptr if it's not that type
	or if the object is nullptr. */
template<class T> T *TBSafeCast(TBTypedObject *obj) {
	return obj ? obj->SafeCastTo<T>() : nullptr;
}

/** Returns the given object as the given type, or nullptr if it's not that type
	or if the object is nullptr. */
template<class T> const T *TBSafeCast(const TBTypedObject *obj) {
	return obj ? obj->SafeCastTo<T>() : nullptr;
}

/** Implement the methods for safe typecasting without requiring RTTI. */
#define TBOBJECT_SUBCLASS(clazz, baseclazz) \
	virtual const char *GetClassName() const override { return #clazz; } \
	virtual bool IsOfTypeId(const tb::TB_TYPE_ID type_id) const override \
		{ return GetTypeId<clazz>() == type_id ? true : baseclazz::IsOfTypeId(type_id); } \
	static const char* TypeName() { return #clazz; }

} // namespace tb

#endif // TB_OBJECT_H
