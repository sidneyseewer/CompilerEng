#include "SymbolTable.h"

// Abstract class Type
class Type {
public:
    virtual ~Type() = default;

    virtual std::string getTypeName() const = 0;
};

// Concrete class representing a base type
class BaseType : public Type {
public:
    BaseType(const std::string& typeName, size_t size)
        : typeName(typeName), size(size) {}

    std::string getTypeName() const override {
        return typeName;
    }

    size_t getSize() const {
        return size;
    }

private:
    std::string typeName;
    size_t size;
};

// Abstract class Symbol
class Symbol {
public:
    Symbol(const std::string& name) : name(name) {}
    virtual ~Symbol() = default;

    const std::string& getName() const {
        return name;
    }

    virtual Type getType() const = 0;

private:
    std::string name;
};

// Concrete class representing a specific type of symbol
class VariableSymbol : public Symbol {
public:
    VariableSymbol(const std::string& name, const BaseType& type){
        this->type = type;
        this->name = name;
    }

    BaseType getType() const override {
        return type;
    }

private:
    BaseType type;
};

// Singleton class SymbolTable
class SymbolTable {
public:
    // Method to add a symbol to the table
    void Add(Symbol* symbol) {
        symbols[symbol->getName()] = symbol;
    }

    // Method to find a symbol in the table
    Symbol* Find(const std::string& name) {
        auto it = symbols.find(name);
        if (it != symbols.end()) {
            return it->second;
        }
        return nullptr;
    }

    // Method to get the singleton instance of SymbolTable
    static SymbolTable& GetInstance() {
        static SymbolTable instance;
        return instance;
    }

    // Method to delete the singleton instance of SymbolTable
    static void DeleteInstance() {
        SymbolTable& instance = GetInstance();
        delete& instance;
    }

private:
    // Private constructor to enforce singleton pattern
    SymbolTable() {}

    // Destructor to clean up resources
    ~SymbolTable() {
        for (auto& entry : symbols) {
            delete entry.second;
        }
        symbols.clear();
    }

    // Private copy constructor and assignment operator to prevent copying
    SymbolTable(const SymbolTable&) = delete;
    SymbolTable& operator=(const SymbolTable&) = delete;

    std::unordered_map<std::string, Symbol*> symbols;
};