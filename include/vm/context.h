#ifndef CONTEXT_H_
#define CONTEXT_H_

#include <memory>
#include <list>
#include "ast/value/value.h"

namespace apus {

    class Context {
    public:

        Context();
        virtual ~Context();

        inline bool GetBreak() { return break_; }
        inline bool GetContinue() { return continue_; }
        inline bool GetReturn() { return return_; }
        inline bool GetExit() { return exit_; }
        std::shared_ptr<Value> GetReturnType() { return return_type_; }
        std::list<std::shared_ptr<Value>> GetArgList() { return arg_list_; }

        inline void SetBreak(bool _break) { break_ = _break;}
        inline void SetContinue(bool _continue) { continue_ = _continue;}
        inline void SetReturn(bool _return) { return_ = _return; }
        inline void SetExit(bool _exit) { exit_ = _exit; }
        void SetReturnType(std::shared_ptr<Value> _return_type) { return_type_ = _return_type; }
        void SetArgList(std::list<std::shared_ptr<Value>> _arg_list) { arg_list_ = _arg_list; }

    private:

        bool break_;
        bool continue_;
        bool return_;
        bool exit_;

        std::list<std::shared_ptr<Value>> arg_list_;
        std::shared_ptr<Value> return_type_;

    };

}

#endif
