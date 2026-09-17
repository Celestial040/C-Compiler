#include <stdint.h>
#include <stddef.h>
#include "bool.h"

// ==========================================
// 1. Packed Enum Types (Guaranteed 1 Byte)
// ==========================================

typedef uint8_t TokenKind;
enum {
    TOK_KEYWORD,
    TOK_OPERATOR,
    TOK_PUNCTUATION,
    TOK_IDENTIFIER,
    TOK_LITERAL_INT,
    TOK_LITERAL_FLOAT,
    TOK_LITERAL_STRING,
    TOK_EOF
};

typedef uint8_t SymbolKind;
enum {
    SYMBOL_NONE = 0,
    SYMBOL_KEYWORD,
    SYMBOL_IDENTIFIER,
    SYMBOL_TYPEDEF_NAME,
    SYMBOL_VARIABLE,
    SYMBOL_FUNCTION,
    SYMBOL_STRUCT_TAG,
    SYMBOL_UNION_TAG,
    SYMBOL_ENUM_TAG,
    SYMBOL_ENUM_CONSTANT
};

// ==========================================
// 2. Token Layout (8 Bytes Total)
// ==========================================

typedef struct Token {
    uint32_t symbol_id;  // 32-bit ID pointing to SymbolPool index
    TokenKind kind;      // High-level token classification
    uint8_t sub_kind;    // Keyword ID, Operator ID, or Punctuation ID
    uint16_t line;       // Line number for error reporting
} Token;

// ==========================================
// 3. Symbol Metadata Layout (24 Bytes)
// ==========================================

typedef struct SymbolEntry {
    const char *name;     // Pointer to string data in arena
    uint16_t length;      // String byte length
    SymbolKind kind;      // Semantic role (Variable, Func, Typedef...)
    TokenKind token_kind;
    uint8_t sub_kind;
    uint8_t scope_depth;  // Nesting level where symbol was declared
    uint32_t flags;       // Attributes (const, static, extern, inline...)
    void *payload;        // Pointer to type descriptor or AST node
} SymbolEntry;

// ==========================================
// 4. Hash Map Slot (16 Bytes Total)
// ==========================================

typedef struct HashSlot {
    uint32_t hash;        // 32-bit string hash (e.g. FNV-1a)
    uint32_t symbol_id;   // Index into SymbolPool.entries array
    uint16_t probe_count; // Distance from ideal bucket (Robin Hood)
    uint16_t pad;         // Alignment padding
    uint32_t reserved;    // Future expansion / cache boundary alignment
} HashSlot;

// ==========================================
// 5. Hash Map & Symbol Pool Containers
// ==========================================

typedef struct StringHashMap {
    HashSlot *slots;      // Dense bucket array (Power of 2 capacity)
    uint32_t capacity;    // Total slots available
    uint32_t count;       // Total items currently inserted
    uint32_t mask;        // Precalculated capacity - 1 for fast bitwise AND
} StringHashMap;

typedef struct SymbolPool {
    SymbolEntry *entries; // Flat array indexed directly by symbol_id
    uint32_t count;       // Total unique interned strings
    uint32_t capacity;    // Total capacity of entries array
    StringHashMap map;    // Lookup map to convert string -> symbol_id
} SymbolPool;
