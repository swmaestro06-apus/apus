#include <list>
#include <memory>

#include "gtest/gtest.h"

#include "ast/expression.h"
#include "ast/statement/statement.h"

#include "ast/value/signed_int_value.h"
#include "ast/value/float_value.h"

#include "vm/context.h"

using namespace apus;

TEST (ASTTest, Expression_nullptr) {

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
}

// add, sub, mul, div and modulo
TEST (ASTTest, Expression_ASMD) {

    apus::Context ctx;

    // 1 + 2 == 3
    {
        std::shared_ptr<Value> left_value = std::make_shared<SignedIntValue>(S32, 1);
        std::shared_ptr<Expression> left_expr = std::make_shared<ValueExpression>(left_value);

        std::shared_ptr<Value> right_value = std::make_shared<SignedIntValue>(S32, 2);
        std::shared_ptr<Expression> right_expr = std::make_shared<ValueExpression>(right_value);
        std::shared_ptr<Expression> expr = std::make_shared<BinaryExpression>(Expression::EXP_ADD, left_expr, right_expr);

        std::shared_ptr<SignedIntValue> result = std::dynamic_pointer_cast<SignedIntValue>(expr->Evaluate(ctx));

        EXPECT_EQ(3, result->getIntValue());
    }

    // 1 + 2 * 3 == 7
    {
        std::shared_ptr<Expression> _1 = std::make_shared<ValueExpression>(std::make_shared<SignedIntValue>(S32, 1));
        std::shared_ptr<Expression> _2 = std::make_shared<ValueExpression>(std::make_shared<SignedIntValue>(S32, 2));
        std::shared_ptr<Expression> _3 = std::make_shared<ValueExpression>(std::make_shared<SignedIntValue>(S32, 3));

        std::shared_ptr<Expression> mul_expr = std::make_shared<BinaryExpression>(Expression::EXP_MUL, _2, _3);
        std::shared_ptr<Expression> add_expr = std::make_shared<BinaryExpression>(Expression::EXP_ADD, _1, mul_expr);

        std::shared_ptr<SignedIntValue> result = std::dynamic_pointer_cast<SignedIntValue>(add_expr->Evaluate(ctx));

        EXPECT_EQ(7, result->getIntValue());
    }

    // ( 1 + 2 * 3 ) % 5 == 2
    {
        std::shared_ptr<Expression> _1 = std::make_shared<ValueExpression>(std::make_shared<SignedIntValue>(S32, 1));
        std::shared_ptr<Expression> _2 = std::make_shared<ValueExpression>(std::make_shared<SignedIntValue>(S32, 2));
        std::shared_ptr<Expression> _3 = std::make_shared<ValueExpression>(std::make_shared<SignedIntValue>(S32, 3));
        std::shared_ptr<Expression> _5 = std::make_shared<ValueExpression>(std::make_shared<SignedIntValue>(S32, 5));

        std::shared_ptr<Expression> mul_expr = std::make_shared<BinaryExpression>(Expression::EXP_MUL, _2, _3);
        std::shared_ptr<Expression> add_expr = std::make_shared<BinaryExpression>(Expression::EXP_ADD, _1, mul_expr);

        std::shared_ptr<Expression> mod_expr = std::make_shared<BinaryExpression>(Expression::EXP_MOD, add_expr, _5);

        std::shared_ptr<SignedIntValue> result = std::dynamic_pointer_cast<SignedIntValue>(mod_expr->Evaluate(ctx));

        EXPECT_EQ(2, result->getIntValue());
    }

    // 2 * 3.5 / 3
    {
        std::shared_ptr<Expression> _2 = std::make_shared<ValueExpression>(std::make_shared<SignedIntValue>(S64, 2));
        std::shared_ptr<Expression> _3_5 = std::make_shared<ValueExpression>(std::make_shared<FloatValue>(F64, 3.5));
        std::shared_ptr<Expression> _3 = std::make_shared<ValueExpression>(std::make_shared<SignedIntValue>(S64, 3));

        std::shared_ptr<Expression> mul_expr = std::make_shared<BinaryExpression>(Expression::EXP_MUL, _2, _3_5);
        std::shared_ptr<Expression> div_expr = std::make_shared<BinaryExpression>(Expression::EXP_DIV, mul_expr, _3);

        std::shared_ptr<FloatValue> result = std::dynamic_pointer_cast<FloatValue>(div_expr->Evaluate(ctx));

        EXPECT_EQ( (2 * 3.5 / 3) , result->getFloatValue());
    }

}

TEST (ASTTest, Expression_Int_Compare) {

    apus::Context ctx;

    {
        std::shared_ptr<Expression> _2 = std::make_shared<ValueExpression>(std::make_shared<SignedIntValue>(S32, 2));
        std::shared_ptr<Expression> _3 = std::make_shared<ValueExpression>(std::make_shared<SignedIntValue>(S32, 3));

        std::shared_ptr<Expression> eql_expr = std::make_shared<BinaryExpression>(Expression::EXP_EQL, _2, _3);
        std::shared_ptr<Expression> neq_expr = std::make_shared<BinaryExpression>(Expression::EXP_NEQ, _2, _3);
        std::shared_ptr<Expression> lss_expr = std::make_shared<BinaryExpression>(Expression::EXP_LSS, _2, _3);
        std::shared_ptr<Expression> gtr_expr = std::make_shared<BinaryExpression>(Expression::EXP_GTR, _2, _3);
        std::shared_ptr<Expression> leq_expr = std::make_shared<BinaryExpression>(Expression::EXP_LEQ, _2, _3);
        std::shared_ptr<Expression> geq_expr = std::make_shared<BinaryExpression>(Expression::EXP_GEQ, _2, _3);

        std::shared_ptr<SignedIntValue> result = std::dynamic_pointer_cast<SignedIntValue>(eql_expr->Evaluate(ctx));
        EXPECT_EQ( 2 == 3, result->getIntValue());
        result = std::dynamic_pointer_cast<SignedIntValue>(neq_expr->Evaluate(ctx));
        EXPECT_EQ( 2 != 3, result->getIntValue());
        result = std::dynamic_pointer_cast<SignedIntValue>(lss_expr->Evaluate(ctx));
        EXPECT_EQ( 2 < 3, result->getIntValue());
        result = std::dynamic_pointer_cast<SignedIntValue>(gtr_expr->Evaluate(ctx));
        EXPECT_EQ( 2 > 3, result->getIntValue());
        result = std::dynamic_pointer_cast<SignedIntValue>(leq_expr->Evaluate(ctx));
        EXPECT_EQ( 2 <= 3, result->getIntValue());
        result = std::dynamic_pointer_cast<SignedIntValue>(geq_expr->Evaluate(ctx));
        EXPECT_EQ( 2 >= 3, result->getIntValue());

    }
}

TEST (ASTTest, Expression_Float_Compare) {

    apus::Context ctx;

    {
        std::shared_ptr<Expression> _2_5 = std::make_shared<ValueExpression>(std::make_shared<FloatValue>(F32, 2));
        std::shared_ptr<Expression> _3_7 = std::make_shared<ValueExpression>(std::make_shared<FloatValue>(F32, 3));

        std::shared_ptr<Expression> eql_expr = std::make_shared<BinaryExpression>(Expression::EXP_EQL, _2_5, _3_7);
        std::shared_ptr<Expression> neq_expr = std::make_shared<BinaryExpression>(Expression::EXP_NEQ, _2_5, _3_7);
        std::shared_ptr<Expression> lss_expr = std::make_shared<BinaryExpression>(Expression::EXP_LSS, _2_5, _3_7);
        std::shared_ptr<Expression> gtr_expr = std::make_shared<BinaryExpression>(Expression::EXP_GTR, _2_5, _3_7);
        std::shared_ptr<Expression> leq_expr = std::make_shared<BinaryExpression>(Expression::EXP_LEQ, _2_5, _3_7);
        std::shared_ptr<Expression> geq_expr = std::make_shared<BinaryExpression>(Expression::EXP_GEQ, _2_5, _3_7);

        std::shared_ptr<FloatValue> result = std::dynamic_pointer_cast<FloatValue>(eql_expr->Evaluate(ctx));
        EXPECT_EQ( 2.5 == 3.7, result->getFloatValue());
        result = std::dynamic_pointer_cast<FloatValue>(neq_expr->Evaluate(ctx));
        EXPECT_EQ( 2.5 != 3.7, result->getFloatValue());
        result = std::dynamic_pointer_cast<FloatValue>(lss_expr->Evaluate(ctx));
        EXPECT_EQ( 2.5 < 3.7, result->getFloatValue());
        result = std::dynamic_pointer_cast<FloatValue>(gtr_expr->Evaluate(ctx));
        EXPECT_EQ( 2.5 > 3.7, result->getFloatValue());
        result = std::dynamic_pointer_cast<FloatValue>(leq_expr->Evaluate(ctx));
        EXPECT_EQ( 2.5 <= 3.7, result->getFloatValue());
        result = std::dynamic_pointer_cast<FloatValue>(geq_expr->Evaluate(ctx));
        EXPECT_EQ( 2.5 >= 3.7, result->getFloatValue());

    }
}