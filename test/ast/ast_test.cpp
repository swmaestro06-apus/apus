#include <list>
#include <memory>

#include "gtest/gtest.h"

#include "ast/expression.h"
#include "ast/statement/statement.h"

#include "ast/value/signed_int_value.h"
#include "ast/value/float_value.h"

#include "vm/context.h"

using namespace apus;

TEST (ASTTest, ExpressionTest1) {

    apus::Context ctx;

    //  nullptr input
    {
        std::shared_ptr<Expression> left_expr = nullptr;
        std::shared_ptr<Expression> right_expr = nullptr;
        Expression *expr = nullptr;

        expr = new BinaryExpression(Expression::EXP_ADD, left_expr,
                                    right_expr);

        EXPECT_EQ(nullptr, expr->Evaluate(ctx));
    }

    // 1 + 2 == 3
    {
        std::shared_ptr<Value> left_value = std::make_shared<SignedIntValue>(S32, 1);
        std::shared_ptr<Expression> left_expr = std::make_shared<ValueExpression>(left_value);

        std::shared_ptr<Value> right_value = std::make_shared<SignedIntValue>(S32, 2);
        std::shared_ptr<Expression> right_expr = std::make_shared<ValueExpression>(right_value);
        std::shared_ptr<Expression> expr = std::make_shared<BinaryExpression>(Expression::EXP_ADD, left_expr, right_expr);

        std::shared_ptr<SignedIntValue> result = std::dynamic_pointer_cast<SignedIntValue>(expr->Evaluate(ctx));

        EXPECT_EQ(3, result->getValue());
    }

    // 1 + 2 * 3 == 7
    {
        std::shared_ptr<Expression> _1 = std::make_shared<ValueExpression>(std::make_shared<SignedIntValue>(S32, 1));
        std::shared_ptr<Expression> _2 = std::make_shared<ValueExpression>(std::make_shared<SignedIntValue>(S32, 2));
        std::shared_ptr<Expression> _3 = std::make_shared<ValueExpression>(std::make_shared<SignedIntValue>(S32, 3));

        std::shared_ptr<Expression> mul_expr = std::make_shared<BinaryExpression>(Expression::EXP_MUL, _2, _3);
        std::shared_ptr<Expression> add_expr = std::make_shared<BinaryExpression>(Expression::EXP_ADD, _1, mul_expr);

        std::shared_ptr<SignedIntValue> result = std::dynamic_pointer_cast<SignedIntValue>(add_expr->Evaluate(ctx));

        EXPECT_EQ(7, result->getValue());
    }

    // ( 1 + 2 * 3 ) % 5 == 5
    {
        std::shared_ptr<Expression> _1 = std::make_shared<ValueExpression>(std::make_shared<SignedIntValue>(S32, 1));
        std::shared_ptr<Expression> _2 = std::make_shared<ValueExpression>(std::make_shared<SignedIntValue>(S32, 2));
        std::shared_ptr<Expression> _3 = std::make_shared<ValueExpression>(std::make_shared<SignedIntValue>(S32, 3));
        std::shared_ptr<Expression> _5 = std::make_shared<ValueExpression>(std::make_shared<SignedIntValue>(S32, 5));

        std::shared_ptr<Expression> mul_expr = std::make_shared<BinaryExpression>(Expression::EXP_MUL, _2, _3);
        std::shared_ptr<Expression> add_expr = std::make_shared<BinaryExpression>(Expression::EXP_ADD, _1, mul_expr);

        std::shared_ptr<Expression> mod_expr = std::make_shared<BinaryExpression>(Expression::EXP_MOD, add_expr, _5);

        std::shared_ptr<SignedIntValue> result = std::dynamic_pointer_cast<SignedIntValue>(mod_expr->Evaluate(ctx));

        EXPECT_EQ(5, result->getValue());
    }

    // 2 * 3.5 / 3
    {
        std::shared_ptr<Expression> _2 = std::make_shared<ValueExpression>(std::make_shared<SignedIntValue>(S64, 2));
        std::shared_ptr<Expression> _3_5 = std::make_shared<ValueExpression>(std::make_shared<FloatValue>(F64, 3.5));
        std::shared_ptr<Expression> _3 = std::make_shared<ValueExpression>(std::make_shared<SignedIntValue>(S64, 3));

        std::shared_ptr<Expression> mul_expr = std::make_shared<BinaryExpression>(Expression::EXP_MUL, _2, _3_5);
        std::shared_ptr<Expression> div_expr = std::make_shared<BinaryExpression>(Expression::EXP_DIV, mul_expr, _3);

        std::shared_ptr<FloatValue> result = std::dynamic_pointer_cast<FloatValue>(div_expr->Evaluate(ctx));

        EXPECT_EQ( (2 * 3.5 / 3) , result->getValue());
    }
}
