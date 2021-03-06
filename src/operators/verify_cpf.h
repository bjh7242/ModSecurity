/*
 * ModSecurity, http://www.modsecurity.org/
 * Copyright (c) 2015 Trustwave Holdings, Inc. (http://www.trustwave.com/)
 *
 * You may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * If any of the files related to licensing are missing or if you have any
 * other questions related to licensing please contact Trustwave Holdings, Inc.
 * directly using the email address security@modsecurity.org.
 *
 */

#ifndef SRC_OPERATORS_VERIFY_CPF_H_
#define SRC_OPERATORS_VERIFY_CPF_H_

#include <string>

#include "src/operators/operator.h"
#include "src/utils/regex.h"


namespace modsecurity {
using Utils::SMatch;
using Utils::regex_search;
using Utils::Regex;

namespace operators {

class VerifyCPF : public Operator {
 public:
    /** @ingroup ModSecurity_Operator */
    VerifyCPF(std::string o, std::string p, bool n)
        : Operator(o, p, n) {
        m_re = new Regex(p);
    }
    VerifyCPF(std::string name, std::string param)
        : Operator(name, param) {
        m_re = new Regex(param);
    }
    explicit VerifyCPF(std::string param)
        : Operator("VerifyCPF", param) {
        m_re = new Regex(param);
    }

    ~VerifyCPF() {
        delete m_re;
    }
    bool evaluate(Transaction *transaction, Rule *rule,
        const std::string &input) override {
        return evaluate(transaction, NULL, input, NULL);
    }
    bool evaluate(Transaction *transaction,
        const std::string &input) override {
        return evaluate(transaction, NULL, input);
    }
    bool evaluate(Transaction *transaction, Rule *rule,
        const std::string& input,
        std::shared_ptr<RuleMessage> ruleMessage) override;

    int convert_to_int(const char c);
    bool verify(const char *ssnumber, int len);

 private:
    Regex *m_re;
};

}  // namespace operators
}  // namespace modsecurity


#endif  // SRC_OPERATORS_VERIFY_CPF_H_
