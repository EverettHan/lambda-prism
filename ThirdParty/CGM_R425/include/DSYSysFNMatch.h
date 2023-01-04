
#ifndef DSYSysFNMatch_H
#define DSYSysFNMatch_H

/************************************************************************/
/* Declarations                                                         */
/************************************************************************/
enum struct DSYSysFNMCaseBehavior : char
{
    PlatformDefault = 0,
    Sensitive = 1,
    Insensitive = 2
};

enum struct DSYSysFNMBracketBehavior : char
{
    PlatformDefault = 0,
    // RegularChar: means that bracket will be escaped automatically
    // if they have a special meaning on the target platform
    RegularChar = 1,
#if !defined(_WINDOWS_SOURCE)
    // This behavior is not supported on this platform!
    Expression = 2
#endif  // _WINDOWS_SOURCE
};

class DSYSysFNMatchOptions
{
public:
    /**
     * DSYSysFNMatchOptions CTOR
     * Make the choice of options explicit so the user thinks about it,
     * instead of just picking the default!
     */
    explicit DSYSysFNMatchOptions(
        DSYSysFNMCaseBehavior iCase, 
        DSYSysFNMBracketBehavior iBracket)
        : m_OptionCase(iCase), m_OptionBracket(iBracket)
    {
    }
    
    DSYSysFNMCaseBehavior     GetOptionCase() const    { return m_OptionCase; }
    DSYSysFNMBracketBehavior  GetOptionBracket() const { return m_OptionBracket; }
    
    bool operator == (const DSYSysFNMatchOptions & iComparand) const;
    bool operator != (const DSYSysFNMatchOptions & iComparand) const;
    
private:
    DSYSysFNMCaseBehavior    m_OptionCase;
    DSYSysFNMBracketBehavior m_OptionBracket;
};

/************************************************************************/
/* Predefined options                                                   */
/************************************************************************/

/**
 * DSY_FNM_BEHAVIOR_UNIFIED_CASE_SENSITIVE
 * Pattern interpretation is homogeneous across platforms, but supported
 * wildcards are limited to the following:
 *     *    Zero or more characters.
 *     ?    Exactly one character.
 * In this mode, pattern matching is case sensitive.
 */
static const DSYSysFNMatchOptions DSY_FNM_BEHAVIOR_UNIFIED_CASE_SENSITIVE (
    DSYSysFNMCaseBehavior::Sensitive, 
    DSYSysFNMBracketBehavior::RegularChar
);

/**
 * DSY_FNM_BEHAVIOR_UNIFIED_CASE_INSENSITIVE
 * Similar to DSY_FNM_BEHAVIOR_UNIFIED_CASE_SENSITIVE, except that in this
 * mode, pattern matching is case INsensitive.
 */
static const DSYSysFNMatchOptions DSY_FNM_BEHAVIOR_UNIFIED_CASE_INSENSITIVE (
    DSYSysFNMCaseBehavior::Insensitive, 
    DSYSysFNMBracketBehavior::RegularChar
);

/**
 * DSY_FNM_BEHAVIOR_PLATFORM_DEFAULT
 * In this mode, pattern interpretation may vary between platforms.
 * For e.g., pattern matching is case INsensitive on Windows (but generally
 * case sensitive on other platforms).
 * Moreover, while a couple of brackets [ ] is treated as a pair of regular
 * characters on Windows, it has a special meaning on Unix platforms: they
 * form a bracket expression.
 *
 * Provides optimal performance on each platform.
 */
static const DSYSysFNMatchOptions DSY_FNM_BEHAVIOR_PLATFORM_DEFAULT (
    DSYSysFNMCaseBehavior::PlatformDefault, 
    DSYSysFNMBracketBehavior::PlatformDefault
);


/************************************************************************/
/* Implementation                                                       */
/************************************************************************/
inline bool DSYSysFNMatchOptions::operator == (const DSYSysFNMatchOptions & iComparand) const
{
    if(this->m_OptionCase != iComparand.m_OptionCase)
        return false;
    if(this->m_OptionBracket != iComparand.m_OptionBracket)
        return false;
    return true;
}

inline bool DSYSysFNMatchOptions::operator != (const DSYSysFNMatchOptions & iComparand) const
{
    return !(*this == iComparand);
}

#endif  // DSYSysFNMatch_H
