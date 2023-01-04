
#ifndef DSYLazyIID_H
#define DSYLazyIID_H

#include "IUnknown.h"   // IID
#include "CATSysTS.h"   // ExportedByCATSysTS


/**
 * DSYLazyIID.
 * IID guaranteed to be initialized on first access, regardless of variable initialization order.
 * In other words, not subject to Initialization Order Fiasco.
 */
struct DSYLazyIID   // Could be changed to a typedef to a more generic 'DSY::Lazy<IID>'
{
    // With C++20 support, global instances could be initialized at buildtime rather than lazily at runtime, thanks to a constexpr constructor
    /*constexpr?*/ DSYLazyIID() = default;

    operator IID const & () {
        _ensureInit();
        return m_iid;
    }
    
    IID const * operator&() {
        _ensureInit();
        return &m_iid;
    }
    
private:
    void _ensureInit() {
        if(!m_bInit) {  // As a trivial object, expected to be zero initialized => false
            m_bInit = true;
            ExportedByCATSysTS int getuuid_impl(unsigned char u_bits[16]); // Scoped declaration of SystemTS function
            getuuid_impl(reinterpret_cast<unsigned char*>(&m_iid));
        }
    }
    
    IID m_iid;
    bool m_bInit;
};

#endif  // DSYLazyIID_H
