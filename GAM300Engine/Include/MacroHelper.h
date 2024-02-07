#pragma once


#define CREATE_CONST_GETTOR(NAME, RET)\
    inline const RET& Get##NAME() const \
    {\
        return m_##NAME; \
    }

#define CREATE_GETTOR(NAME, RET)\
    inline RET& Get##NAME() \
    {\
        return m_##NAME; \
    }

#define CREATE_NON_REF_GETTOR(NAME, RET)\
    inline RET Get##NAME() \
    {\
        return m_##NAME; \
    }

#define CREATE_SETTOR(NAME, PARAM)\
    inline void Set##NAME(const PARAM& NAME)\
    { \
        m_##NAME = NAME; \
    }

#define DELETE_COPY(TYPE_NAME)                      \
    TYPE_NAME(const TYPE_NAME&)            = delete; \
    TYPE_NAME& operator=(const TYPE_NAME&) = delete;  

#define DELETE_MOVE(TYPE_NAME)                      \
    TYPE_NAME(TYPE_NAME&&)                 = delete; \
    TYPE_NAME& operator=(TYPE_NAME&&)      = delete;

