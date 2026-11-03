#pragma once

#include <memory>
#include <iostream>
#include <string>


class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual void print(int indent = 0) const = 0;
};

class IntNode : public ASTNode {
    int value;
public:
    IntNode(int val) : value(val) {}
    void print(int indent) const override {
        std::cout << std::string(indent, ' ') << "Int: " << value << "\n";
    }
};

class AddNode : public ASTNode {
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;
public:
    AddNode(std::unique_ptr<ASTNode> l, std::unique_ptr<ASTNode> r)
        : left(std::move(l)), right(std::move(r)) {}

    void print(int indent) const override {
        std::cout << std::string(indent, ' ') << "Op: +\n";
        left->print(indent + 2);
        right->print(indent + 2);
    }
};
