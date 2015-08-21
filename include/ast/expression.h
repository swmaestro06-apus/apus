#ifndef EXPRESSION_H_
#define EXPRESSION_H_

#include <memory>
#include <string>

namespace apus {

    class Value;
    class Context;

    class Expression {
    public:

        enum Type {
            EXP_NONE,

            EXP_OR,     // '|'
            EXP_AND,    // '&'

            EXP_EQL,    // '=='
            EXP_NEQ,    // '!='
            EXP_LSS,    // '<'
            EXP_GTR,    // '>'
            EXP_LEQ,    // '<='
            EXP_GEQ,    // '>='

            EXP_LSHIFT, // '<<'
            EXP_RSHIFT, // '>>'

            EXP_ADD,    // '+'
            EXP_SUB,    // '-'
            EXP_MUL,    // '*'
            EXP_DIV,    // '/'
            EXP_MOD,    // '%'
            EXP_REVERSE, // '~'
            EXP_XOR,     // '^'

            EXP_NOT,    // '!'

            EXP_ASSIGN,    // '='
            EXP_ADDASSIGN, // '+='
            EXP_SUBASSIGN, // '-='
            EXP_MULASSIGN, // '*='
            EXP_DIVASSIGN, // '/='
            EXP_MODASSIGN, // '%='
            EXP_ORASSIGN,  // '|='
            EXP_ANDASSIGN, // '&='
            EXP_XORASSIGN, // '^='
            EXP_LSASSIGN,  // '<<='
            EXP_RSASSIGN,  // '>>='

            EXP_LOR,  // '||'
            EXP_LAND, // '&&'

            EXP_UNARY,
            EXP_VALUE,
            EXP_VARIABLE,
            EXP_FUNCTION,
            EXP_MEMBER,   // '.'
        };

        Expression(Type type = EXP_NONE);
        virtual ~Expression();

        virtual Type getType() { return type_; }
        virtual std::shared_ptr<Value> Evaluate(Context& context) = 0;

    protected:
        Type type_;
    };

    class BinaryExpression : public Expression {
    public:
        BinaryExpression(Type type,
                         std::shared_ptr<Expression> leftExpression,
                         std::shared_ptr<Expression> rightExpression);

        BinaryExpression(Type type, Expression* leftExpression,
                         Expression* rightExpression);

        virtual ~BinaryExpression();

        virtual std::shared_ptr<Value> Evaluate(Context& context) override;

    private:

        std::shared_ptr<Expression> left_expression_;
        std::shared_ptr<Expression> right_expression_;

    };

    class UnaryExpression : public Expression {
    public:
        UnaryExpression(Type type, std::shared_ptr<Expression> expression);

        UnaryExpression(Type type, Expression* expression);

        virtual ~UnaryExpression();

        virtual std::shared_ptr<Value> Evaluate(Context& context);

    private:

        std::shared_ptr<Expression> expression_;

    };

    class ValueExpression : public Expression {
    public:
        ValueExpression(std::shared_ptr<Value> value);
        ValueExpression(Value* value);
        virtual ~ValueExpression(){}

        virtual std::shared_ptr<Value> Evaluate(Context& context);

    private:
        std::shared_ptr<Value> value_;
    };

    class VariableExpression : public Expression {
    public:
        VariableExpression(std::string name);
        VariableExpression(char* name);
        virtual ~VariableExpression();

        virtual std::shared_ptr<Value> Evaluate(Context& context);

    private:
        std::string name_;
    };

    class AssignExpression : public Expression {
    public:
        AssignExpression(Type type, std::string name,
                         std::shared_ptr<Expression> expression);
        AssignExpression(Type type, char* name, Expression* expression);
        virtual ~AssignExpression();

        virtual std::shared_ptr<Value> Evaluate(Context& context);

    private:
        std::string name_;
        std::shared_ptr<Expression> expression_;
    };

    class MemberExpression : public Expression {
    public:
        MemberExpression(std::string parent_name, std::string child_name);
        MemberExpression(char* parent_name, char* child_name);
        virtual ~MemberExpression();

        virtual std::shared_ptr<Value> Evaluate(Context& context);

    private:

        std::string parent_name_;
        std::string child_name_;
    };

}

#endif
