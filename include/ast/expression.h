#ifndef EXPRESSION_H_
#define EXPRESSION_H_

#include <memory>

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
            EXP_NOT,    // '!'
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
        UnaryExpression(Type type,
                        std::shared_ptr<Expression> expression);

        UnaryExpression(Type type,
                        Expression* expression);

        UnaryExpression(std::shared_ptr<Value> value);

        UnaryExpression(Value* value);


        virtual ~UnaryExpression();

        virtual std::shared_ptr<Value> Evaluate(Context& context);

    private:

        std::shared_ptr<Expression> expression_;
        std::shared_ptr<Value> value_;

    };

}

#endif
