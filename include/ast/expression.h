#ifndef EXPRESSION_H_
#define EXPRESSION_H_


namespace apus {

    class Expression {
    public:

        virtual std::shared_ptr<Value> Evaluate(Context& context) = 0;
        
    };

}

#endif
