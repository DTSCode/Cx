#include <cstring>
#include "common.h"
#include "parser.h"

extern cx_symtab_node *pProgram_ptr;

/** parse_function_header         parse a function header:
 *
 *                              <type-id> <id> (<parm-list>);
 * 
 *                          or:
 *
 *                              <type-id> <id> (<parm-list>){}
 * 
 * NOTE:
 *      If scope == 0 and pProgram_ptr->found_global_end == false;
 *      Set main's location in icode only when function body is found.
 * 
 * @param p_function_id : ptr to the function id's symbol table node.
 * @return ptr to function id's symbol table node.
 */
cx_symtab_node *cx_parser::parse_function_header(cx_symtab_node *p_function_id) {
    // enter the next__ nesting level and open a new scope
    // for the function.
    symtab_stack.enter_scope();

    //  (
    conditional_get_token_append(tc_left_paren, err_missing_left_paren);

    int parm_count; // count of formal parms
    int total_parm_size; // total byte size of all parms

    cx_symtab_node *pParmList = parse_formal_parm_list(parm_count,
            total_parm_size);

    p_function_id->defn.routine.parm_count = parm_count;
    p_function_id->defn.routine.total_parm_size = total_parm_size;
    p_function_id->defn.routine.locals.p_parms_ids = pParmList;
    p_function_id->defn.how = ::dc_function;

    // Not forwarded.
    p_function_id->defn.routine.locals.p_constant_ids = nullptr;
    p_function_id->defn.routine.locals.p_type_ids = nullptr;
    p_function_id->defn.routine.locals.p_variable_ids = nullptr;
    p_function_id->defn.routine.locals.p_function_ids = nullptr;

    //  )
    conditional_get_token_append(tc_right_paren, err_missing_right_paren);

    if (token == tc_semicolon) {
        p_function_id->defn.routine.which = rc_forward;
    } else if (token == tc_left_bracket) {

        if (!pProgram_ptr->found_global_end) {
            pProgram_ptr->found_global_end = true;
            icode.go_to(pProgram_ptr->global_finish_location);
            icode.put(__MAIN_ENTRY__);
            icode.put(tc_semicolon);
            icode.put(tc_right_bracket);

            // Set the program's icode.
            pProgram_ptr->defn.routine.p_icode = new cx_icode(icode);
        }

        p_function_id->defn.routine.which = rc_declared;
        parse_block(p_function_id);
        p_function_id->defn.routine.return_marker = put_location_marker();
    }

    p_function_id->defn.routine.p_symtab = symtab_stack.exit_scope();

    return p_function_id;
}

/** parse_block      parse a function's block:
 *                      
 *                      {
 *                              <compound-statement>
 *                      }
 * 
 * @param p_function_id : ptr to symbol table node of function's id.
 */
void cx_parser::parse_block(cx_symtab_node *p_function_id) {
    // <compound-statement> : reset the icode and append BEGIN to it,
    //                        and then parse the compound statement.
    resync(tokenlist_statement_start);
    if (token != tc_left_bracket) cx_error(err_missing_left_bracket);
    icode.reset();

    parse_compound(p_function_id);

    // Set the program's or routine's icode.
    p_function_id->defn.routine.p_icode = new cx_icode(icode);
}
