#ifndef GUARD_TYPEINFO_H
#define GUARD_TYPEINFO_H

#include<typeinfo>

class TypeInfo {
public:
	TypeInfo() {
		// needed for containers
		pInfo_ = nullptr;
	};

	TypeInfo(const std::type_info& ti) {
		pInfo_ = &ti;
	};

	TypeInfo(const TypeInfo& fic) {
		pInfo_ = fic.pInfo_;
	};

	inline TypeInfo& operator=(const TypeInfo& fic) {
		this->pInfo_ = &fic.get();
		return *this;
	};

	inline bool before(const TypeInfo& rhs) const {
		return pInfo_->before(rhs.get());
	};

	inline const char* name() const {
		return pInfo_->name();
	};

	inline const std::type_info& get() const {
		return *pInfo_;
	}

private:
	const std::type_info* pInfo_;
};


// Note: Because of the conversion constructor that accepts a std::type_info as a parameters,
// you can directly compare objects of type TypeInfo and std::type_info.

// Comparison operators -- compare shapes, and no need to distinguish identicals.
bool operator==(const TypeInfo& lhs, const TypeInfo& rhs) {
	return lhs.get() == rhs.get();
};
bool operator!=(const TypeInfo& lhs, const TypeInfo& rhs) {
	return !(lhs == rhs);
};
bool operator< (const TypeInfo& lhs, const TypeInfo& rhs) {
	return lhs.before(rhs);
};
bool operator> (const TypeInfo& lhs, const TypeInfo& rhs) {
	return rhs < lhs;
};
bool operator<=(const TypeInfo& lhs, const TypeInfo& rhs) {
	return !(lhs > rhs);
};
bool operator>=(const TypeInfo& lhs, const TypeInfo& rhs) {
	return !(lhs < rhs);
};

#endif
