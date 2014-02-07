/*
* File:   stdio.h
* Author: aaro3965
*
* Created on Feburary 1, 2014, 10:56 PM
*/

#ifndef CX_STDIO_H
#define	CX_STDIO_H

class cx_executor;
class cx_symtab;
class cx_symtab_node;
class cx_type;

class cx_stdio {
public:

	static cx_type *puts(cx_executor *cx,
		cx_symtab_node *cx_function_id,
		const cx_type *p_type);

	static cx_type *open(cx_executor *cx,
		cx_symtab_node *cx_function_id,
		const cx_type *p_type);

	static cx_type *reopen(cx_executor *cx,
		cx_symtab_node *cx_function_id,
		const cx_type *p_type);

	static cx_type *close(cx_executor *cx,
		cx_symtab_node *cx_function_id,
		const cx_type *p_type);

	static cx_type *flush(cx_executor *cx,
		cx_symtab_node *cx_function_id,
		const cx_type *p_type);

	static cx_type *wide(cx_executor *cx,
		cx_symtab_node *cx_function_id,
		const cx_type *p_type);

	/*static cx_type *setbuf(cx_executor *cx,
		cx_symtab_node *cx_function_id,
		const cx_type *p_type);*/

	static cx_type *read(cx_executor *cx,
		cx_symtab_node *cx_function_id,
		const cx_type *p_type);
};

extern cx_symtab *std_stream_members;

#endif	/* CX_STDIO_H */

