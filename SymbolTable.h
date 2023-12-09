#pragma once
#include <string>
#include <unordered_map>

class Parser;
class Errors;

// Abstract class Type
class Type {
public:
    virtual ~Type() = default;

    virtual std::string getTypeName() const = 0;
};

// Concrete class representing a base type
class BaseType : public Type {
public:
    BaseType(const std::string& typeName, size_t size);

    std::string getTypeName() const override;
    size_t getSize() const;

private:
    std::string typeName;
    size_t size;
};

// Abstract class Symbol
class Symbol {
public:
    Symbol(const std::string& name);
    virtual ~Symbol() = default;

    const std::string& getName() const;

    virtual BaseType getType();

private:
    std::string name;
};

// Concrete class representing a specific type of symbol
class VariableSymbol : public Symbol {
public:
    VariableSymbol(const std::string& name, const BaseType& type);

    BaseType getType();

private:
    BaseType type;
};

// Singleton class SymbolTable
class SymbolTable {
public:
    // Method to add a symbol to the table
    void Add(Symbol* symbol);

    // Method to find a symbol in the table
    Symbol* Find(const std::string& name);

    // Method to get the singleton instance of SymbolTable
    static SymbolTable& GetInstance();

    // Method to delete the singleton instance of SymbolTable
    static void DeleteInstance();

private:
    // Private constructor to enforce singleton pattern
    SymbolTable() {}

    // Destructor to clean up resources
    ~SymbolTable();

    // Private copy constructor and assignment operator to prevent copying
    SymbolTable(const SymbolTable&) = delete;
    SymbolTable& operator=(const SymbolTable&) = delete;

    std::unordered_map<std::string, Symbol*> map;
};