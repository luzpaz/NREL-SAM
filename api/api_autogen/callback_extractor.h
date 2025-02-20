/**
BSD-3-Clause
Copyright 2019 Alliance for Sustainable Energy, LLC
Redistribution and use in source and binary forms, with or without modification, are permitted provided
that the following conditions are met :
1.	Redistributions of source code must retain the above copyright notice, this list of conditions
and the following disclaimer.
2.	Redistributions in binary form must reproduce the above copyright notice, this list of conditions
and the following disclaimer in the documentation and/or other materials provided with the distribution.
3.	Neither the name of the copyright holder nor the names of its contributors may be used to endorse
or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT HOLDER, CONTRIBUTORS, UNITED STATES GOVERNMENT OR UNITED STATES
DEPARTMENT OF ENERGY, NOR ANY OF THEIR EMPLOYEES, BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
OR CONSEQUENTIAL DAMAGES(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef SYSTEM_ADVISOR_MODEL_CALLBACK_EXTRACTOR_H
#define SYSTEM_ADVISOR_MODEL_CALLBACK_EXTRACTOR_H

#include <string>
#include <vector>


#include "equations.h"
#include "lk_env.h"
#include "data_structures.h"
#include "lk_eval.h"
#include "config_extractor.h"

class callback_extractor{
private:

    std::string config_name;

    lk::env_t* m_env;

    std::vector<std::string> errors;


    int invoke_method_type(const std::string &method_name);

    bool invoke_function(lk::node_t *root, std::string f_name);


public:

    callback_extractor(std::string n, lk::env_t& e){
        config_name = n;
        m_env = &e;
        m_env->register_funcs( lk::stdlib_basic() );
        m_env->register_funcs( lk::stdlib_sysio() );
        m_env->register_funcs( lk::stdlib_math() );
        m_env->register_funcs( lk::stdlib_string() );
        m_env->register_funcs( invoke_ssc_funcs() );
        m_env->register_funcs( invoke_casecallback_funcs() );
    };

    size_t parse_cmod_statement(std::string callback_script, size_t pos_start);

    /// runs the callback script and saves each function in m_env
    bool parse_script(std::string callback_script);

    /// invokes each function
    bool extract_functions();

};

#endif //SYSTEM_ADVISOR_MODEL_CALLBACK_EXTRACTOR_H
