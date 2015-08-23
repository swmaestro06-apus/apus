#include <list>
#include <memory>

#include "gtest/gtest.h"

#include "ast/expression.h"
#include "ast/statement/statement.h"

#include "ast/value/signed_int_value.h"
#include "ast/value/float_value.h"

#include "vm/context.h"

using namespace apus;

apus::Context ctx;

TEST (ASTTest, Expression_nullptr) {

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

    // 1 + 2 == 3
    {
        std::shared_ptr<Value> left_value = SignedIntValue::Create(S32, 1);
        std::shared_ptr<Expression> left_expr = std::make_shared<ValueExpression>(left_value);

        std::shared_ptr<Value> right_value = SignedIntValue::Create(S32, 2);
        std::shared_ptr<Expression> right_expr = std::make_shared<ValueExpression>(right_value);
        std::shared_ptr<Expression> expr = std::make_shared<BinaryExpression>(Expression::EXP_ADD, left_expr, right_expr);

        std::shared_ptr<SignedIntValue> result = std::dynamic_pointer_cast<SignedIntValue>(expr->Evaluate(ctx));

        EXPECT_EQ(3, result->getIntValue());
    }

    // 1 + 2 * 3 == 7
    {
        std::shared_ptr<Expression> _1 = std::make_shared<ValueExpression>(SignedIntValue::Create(S32, 1));
        std::shared_ptr<Expression> _2 = std::make_shared<ValueExpression>(SignedIntValue::Create(S32, 2));
        std::shared_ptr<Expression> _3 = std::make_shared<ValueExpression>(SignedIntValue::Create(S32, 3));

        std::shared_ptr<Expression> mul_expr = std::make_shared<BinaryExpression>(Expression::EXP_MUL, _2, _3);
        std::shared_ptr<Expression> add_expr = std::make_shared<BinaryExpression>(Expression::EXP_ADD, _1, mul_expr);

        std::shared_ptr<SignedIntValue> result = std::dynamic_pointer_cast<SignedIntValue>(add_expr->Evaluate(ctx));

        EXPECT_EQ(7, result->getIntValue());
    }

    // ( 1 + 2 * 3 ) % 5 == 2
    {
        std::shared_ptr<Expression> _1 = std::make_shared<ValueExpression>(SignedIntValue::Create(S32, 1));
        std::shared_ptr<Expression> _2 = std::make_shared<ValueExpression>(SignedIntValue::Create(S32, 2));
        std::shared_ptr<Expression> _3 = std::make_shared<ValueExpression>(SignedIntValue::Create(S32, 3));
        std::shared_ptr<Expression> _5 = std::make_shared<ValueExpression>(SignedIntValue::Create(S32, 5));

        std::shared_ptr<Expression> mul_expr = std::make_shared<BinaryExpression>(Expression::EXP_MUL, _2, _3);
        std::shared_ptr<Expression> add_expr = std::make_shared<BinaryExpression>(Expression::EXP_ADD, _1, mul_expr);

        std::shared_ptr<Expression> mod_expr = std::make_shared<BinaryExpression>(Expression::EXP_MOD, add_expr, _5);

        std::shared_ptr<SignedIntValue> result = std::dynamic_pointer_cast<SignedIntValue>(mod_expr->Evaluate(ctx));

        EXPECT_EQ(2, result->getIntValue());
    }

    // 2 * 3.5 / 3
    {
        std::shared_ptr<Expression> _2 = std::make_shared<ValueExpression>(SignedIntValue::Create(S64, 2));
        std::shared_ptr<Expression> _3_5 = std::make_shared<ValueExpression>(FloatValue::Create(F64, 3.5));
        std::shared_ptr<Expression> _3 = std::make_shared<ValueExpression>(SignedIntValue::Create(S64, 3));

        std::shared_ptr<Expression> mul_expr = std::make_shared<BinaryExpression>(Expression::EXP_MUL, _2, _3_5);
        std::shared_ptr<Expression> div_expr = std::make_shared<BinaryExpression>(Expression::EXP_DIV, mul_expr, _3);

        std::shared_ptr<FloatValue> result = std::dynamic_pointer_cast<FloatValue>(div_expr->Evaluate(ctx));

        EXPECT_EQ( (2 * 3.5 / 3) , result->getFloatValue());
    }

    // 2 * 3.5 (S16 * F32)
    {
        std::shared_ptr<Expression> _2 = std::make_shared<ValueExpression>(SignedIntValue::Create(S16, 2));
        std::shared_ptr<Expression> _3_5 = std::make_shared<ValueExpression>(FloatValue::Create(F32, 3.5));

        std::shared_ptr<Expression> mul_expr = std::make_shared<BinaryExpression>(Expression::EXP_MUL, _2, _3_5);

        std::shared_ptr<FloatValue> result = std::dynamic_pointer_cast<FloatValue>(mul_expr->Evaluate(ctx));

        EXPECT_EQ( (2 * 3.5) , result->getFloatValue());
    }

    // 2 * 3.5 (S64 * F32)
    {
        std::shared_ptr<Expression> _2 = std::make_shared<ValueExpression>(SignedIntValue::Create(S64, 2));
        std::shared_ptr<Expression> _3_5 = std::make_shared<ValueExpression>(FloatValue::Create(F32, 3.5));

        std::shared_ptr<Expression> mul_expr = std::make_shared<BinaryExpression>(Expression::EXP_MUL, _2, _3_5);

        std::shared_ptr<FloatValue> result = std::dynamic_pointer_cast<FloatValue>(mul_expr->Evaluate(ctx));

        EXPECT_EQ( (2 * 3.5) , result->getFloatValue());
    }

}

TEST (ASTTest, Expression_Int_Compare) {

    {
        std::shared_ptr<Expression> _2 = std::make_shared<ValueExpression>(SignedIntValue::Create(S32, 2));
        std::shared_ptr<Expression> _3 = std::make_shared<ValueExpression>(SignedIntValue::Create(S32, 3));

        std::shared_ptr<Expression> eql_expr = std::make_shared<BinaryExpression>(Expression::EXP_EQL, _2, _3);
        std::shared_ptr<Expression> neq_expr = std::make_shared<BinaryExpression>(Expression::EXP_NEQ, _2, _3);
        std::shared_ptr<Expression> lss_expr = std::make_shared<BinaryExpression>(Expression::EXP_LSS, _2, _3);
        std::shared_ptr<Expression> gtr_expr = std::make_shared<BinaryExpression>(Expression::EXP_GTR, _2, _3);
        std::shared_ptr<Expression> leq_expr = std::make_shared<BinaryExpression>(Expression::EXP_LEQ, _2, _3);
        std::shared_ptr<Expression> geq_expr = std::make_shared<BinaryExpression>(Expression::EXP_GEQ, _2, _3);

        std::shared_ptr<SignedIntValue> result = std::dynamic_pointer_cast<SignedIntValue>(eql_expr->Evaluate(ctx));
        EXPECT_FALSE(result->getIntValue());
        result = std::dynamic_pointer_cast<SignedIntValue>(neq_expr->Evaluate(ctx));
        EXPECT_TRUE(result->getIntValue());
        result = std::dynamic_pointer_cast<SignedIntValue>(lss_expr->Evaluate(ctx));
        EXPECT_TRUE(result->getIntValue());
        result = std::dynamic_pointer_cast<SignedIntValue>(gtr_expr->Evaluate(ctx));
        EXPECT_FALSE(result->getIntValue());
        result = std::dynamic_pointer_cast<SignedIntValue>(leq_expr->Evaluate(ctx));
        EXPECT_TRUE(result->getIntValue());
        result = std::dynamic_pointer_cast<SignedIntValue>(geq_expr->Evaluate(ctx));
        EXPECT_FALSE(result->getIntValue());

    }
}

TEST (ASTTest, Expression_Float_Compare) {

    const double __2_5 = 2.000000000005;
    const double __2_7 = 2.000000000007;

    {
        std::shared_ptr<Expression> _2_5 = std::make_shared<ValueExpression>(FloatValue::Create(F32, __2_5));
        std::shared_ptr<Expression> _2_7 = std::make_shared<ValueExpression>(FloatValue::Create(F32, __2_7));

        std::shared_ptr<Expression> eql_expr = std::make_shared<BinaryExpression>(Expression::EXP_EQL, _2_5, _2_7);
        std::shared_ptr<Expression> neq_expr = std::make_shared<BinaryExpression>(Expression::EXP_NEQ, _2_5, _2_7);
        std::shared_ptr<Expression> lss_expr = std::make_shared<BinaryExpression>(Expression::EXP_LSS, _2_5, _2_7);
        std::shared_ptr<Expression> gtr_expr = std::make_shared<BinaryExpression>(Expression::EXP_GTR, _2_5, _2_7);
        std::shared_ptr<Expression> leq_expr = std::make_shared<BinaryExpression>(Expression::EXP_LEQ, _2_5, _2_7);
        std::shared_ptr<Expression> geq_expr = std::make_shared<BinaryExpression>(Expression::EXP_GEQ, _2_5, _2_7);

        std::shared_ptr<FloatValue> result = std::dynamic_pointer_cast<FloatValue>(eql_expr->Evaluate(ctx));
        EXPECT_FALSE(result->getFloatValue());
        result = std::dynamic_pointer_cast<FloatValue>(neq_expr->Evaluate(ctx));
        EXPECT_TRUE(result->getFloatValue());
        result = std::dynamic_pointer_cast<FloatValue>(lss_expr->Evaluate(ctx));
        EXPECT_TRUE(result->getFloatValue());
        result = std::dynamic_pointer_cast<FloatValue>(gtr_expr->Evaluate(ctx));
        EXPECT_FALSE(result->getFloatValue());
        result = std::dynamic_pointer_cast<FloatValue>(leq_expr->Evaluate(ctx));
        EXPECT_TRUE(result->getFloatValue());
        result = std::dynamic_pointer_cast<FloatValue>(geq_expr->Evaluate(ctx));
        EXPECT_FALSE(result->getFloatValue());

    }
}

TEST (ASTTest, Expression_Float_EQL_Compare) {

    const double a = 0.15 + 0.15;
    const double b = 0.1 + 0.2;

    std::shared_ptr<Expression> a_ = std::make_shared<ValueExpression>(FloatValue::Create(F64, a));
    std::shared_ptr<Expression> b_ = std::make_shared<ValueExpression>(FloatValue::Create(F64, b));

    std::shared_ptr<Expression> eql_expr = std::make_shared<BinaryExpression>(Expression::EXP_EQL, a_, b_);
    std::shared_ptr<Expression> neq_expr = std::make_shared<BinaryExpression>(Expression::EXP_NEQ, a_, b_);
    std::shared_ptr<Expression> leq_expr = std::make_shared<BinaryExpression>(Expression::EXP_LEQ, a_, b_);

    // a == b
    std::shared_ptr<FloatValue> result = std::dynamic_pointer_cast<FloatValue>(eql_expr->Evaluate(ctx));
    EXPECT_TRUE(result->getFloatValue());

    // a != b
    result = std::dynamic_pointer_cast<FloatValue>(neq_expr->Evaluate(ctx));
    EXPECT_FALSE(result->getFloatValue());

    // a <= b
    result = std::dynamic_pointer_cast<FloatValue>(leq_expr->Evaluate(ctx));
    EXPECT_TRUE(result->getFloatValue());

}

TEST (ASTTest, IsTrue) {

    bool result = false;

    result = Value::IsTrue(SignedIntValue::Create(S32, 123));
    EXPECT_TRUE(result);

    result = Value::IsTrue(SignedIntValue::Create(S32, 0));
    EXPECT_FALSE(result);

    result = Value::IsTrue(FloatValue::Create(F32, 123.4));
    EXPECT_TRUE(result);

    result = Value::IsTrue(FloatValue::Create(F32, 0));
    EXPECT_FALSE(result);

}
