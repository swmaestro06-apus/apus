#ifndef CONTEXT_H_
#define CONTEXT_H_

namespace apus {

    class Context {
    public:

        Context();
        virtual ~Context();

        inline bool GetBreak() { return break_; }
        inline bool GetContinue() { return continue_; }
        inline bool GetReturn() { return return_; }
        inline bool GetExit() { return exit_; }

        inline void SetBreak(bool _break) { break_ = _break;}
        inline void SetContinue(bool _continue) { continue_ = _continue;}
        inline void SetReturn(bool _return) { return_ = _return; }
        inline void SetExit(bool _exit) { exit_ = _exit; }

    private:

        bool break_;
        bool continue_;
        bool return_;
        bool exit_;

    };

}

#endif
