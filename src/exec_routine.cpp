//  *************************************************************
//  *                                                           *
//  *   E X E C U T O R   (Routines)                     	*
//  *                                                           *
//  *   Execute programs, procedures, and functions, and calls	*
//  *	to declared and standard subroutines.			*
//  *                                                           *
//  *	CLASSES: TExecutor					*
//  *                                                           *
//  *   FILE:    prog10-1/execrtn.cpp                           *
//  *                                                           *
//  *   MODULE:  Executor                                       *
//  *                                                           *
//  *   Copyright (c) 1995 by Ronald Mak                        *
//  *   For instructional purposes only.  No warranties.        *
//  *                                                           *
//  *************************************************************

#include <memory.h>
#include "common.h"
#include "exec.h"

//--------------------------------------------------------------
//  ExecuteRoutine    	Execute a program, procedure, or
//			function.
//--------------------------------------------------------------

void TExecutor::ExecuteRoutine(TSymtabNode *pRoutineId) {

    EnterRoutine(pRoutineId);

    ExecuteCompound(pRoutineId);

    ExitRoutine(pRoutineId);
}

//--------------------------------------------------------------
//  EnterRoutine    	Enter a routine:  Switch to its
//			intermediate code and allocate its
//			local variables on the runtime stack.
//
//	pRoutineId : ptr to routine name's symbol table node
//--------------------------------------------------------------

void TExecutor::EnterRoutine(TSymtabNode * pRoutineId) {
    TSymtabNode *pId; // ptr to local variable's symtab node

    TraceRoutineEntry(pRoutineId);

    //--Allocate the callee's local variables.
    for (pId = pRoutineId->defn.routine.locals.pVariableIds;
            pId;
            pId = pId->next) runStack.AllocateValue(pId);

    //--Switch to the callee's intermediate code.
    pIcode = pRoutineId->defn.routine.pIcode;
    pIcode->Reset();

}

//--------------------------------------------------------------
//  ExitRoutine    	Exit a routine:  Deallocate its local
//			parameters and variables, pop its frame
//			off the runtime stack, and return to the
//			caller's intermediate code.
//
//	pRoutineId : ptr to routine name's symbol table node
//--------------------------------------------------------------

void TExecutor::ExitRoutine(TSymtabNode *pRoutineId) {
    TSymtabNode *pId; // ptr to symtab node of local variable or parm

    TraceRoutineExit(pRoutineId);

    //--Deallocate local parameters and variables.
    for (pId = pRoutineId->defn.routine.locals.pParmsIds;
            pId;
            pId = pId->next) runStack.DeallocateValue(pId);
    for (pId = pRoutineId->defn.routine.locals.pVariableIds;
            pId;
            pId = pId->next) runStack.DeallocateValue(pId);

    //--Pop off the callee's stack frame and return to the caller's
    //--intermediate code.
    runStack.PopFrame(pRoutineId, pIcode);
}

//--------------------------------------------------------------
//  ExecuteSubroutineCall	Execute a call to a procedure or
//				or a function.
//
//	pRoutineId : ptr to the subroutine name's symtab node
//
//  Return: ptr to the call's type object
//--------------------------------------------------------------

TType *TExecutor::ExecuteSubroutineCall(TSymtabNode *pRoutineId) {
    /*return pRoutineId->defn.routine.which == rcDeclared
                ? ExecuteDeclaredSubroutineCall(pRoutineId)
                : ExecuteStandardSubroutineCall(pRoutineId);*/
    return ExecuteDeclaredSubroutineCall(pRoutineId);
}

//--------------------------------------------------------------
//  ExecuteDeclaredSubroutineCall   Execute a call to a declared
//				    procedure or function.
//
//	pRoutineId : ptr to the subroutine name's symtab node
//
//  Return: ptr to the call's type object
//--------------------------------------------------------------

//int return_level;

TType *TExecutor::ExecuteDeclaredSubroutineCall
(TSymtabNode *pRoutineId) {
    int oldLevel = currentNestingLevel; // level of caller
    int newLevel = pRoutineId->level + 1; // level of callee's locals

    //--Set up a new stack frame for the callee.
    TStackItem *pNewFrameBase = runStack.PushFrameHeader
            (oldLevel, newLevel, pIcode);

    //--Push actual parameter values onto the stack.
    GetToken();

    if (token == tcLParen) {
        ExecuteActualParameters(pRoutineId);
    }

    //-- )
    GetToken();

    //--Activate the new stack frame ...
    currentNestingLevel = newLevel;
    runStack.ActivateFrame(pNewFrameBase, CurrentLocation() - 1);

    //--... and execute the callee.
    ExecuteRoutine(pRoutineId);

    //--Return to the caller.  Restore the current token.
    currentNestingLevel = oldLevel;
    GetToken();

    return pRoutineId->pType;
}

//--------------------------------------------------------------
//  ExecuteActualParameters	Execute the actual parameters of
//				a declared subroutine call.
//
//	pRoutineId : ptr to the subroutine name's symtab node
//--------------------------------------------------------------

void TExecutor::ExecuteActualParameters(TSymtabNode *pRoutineId) {
    TSymtabNode *pFormalId; // ptr to formal parm's symtab node

    //--Loop to execute each actual parameter.
    for (pFormalId = pRoutineId->defn.routine.locals.pParmsIds;
            pFormalId;
            pFormalId = pFormalId->next) {

        TType *pFormalType = pFormalId->pType;
        GetToken();

        //--VAR parameter: ExecuteVariable will leave the actual
        //--		   parameter's addresss on top of the stack.
        if (pFormalId->defn.how == dcReference) {
            ExecuteVariable(pNode, true);
            pFormalId->runstackItem = TOS();
            GetToken();
        }//--Value parameter
        else {
            TType *pActualType = ExecuteExpression();

            if ((pFormalType == pFloatType) &&
                    (pActualType->Base() == pIntegerType)) {

                //--real formal := integer actual:
                //--Convert integer value to real.
                Push(float(Pop()->__int));
                pFormalId->runstackItem = TOS();
            } else if (!pFormalType->IsScalar()) {

                //--Formal parameter is an array or a record:
                //--Make a copy of the actual parameter's value.
                void *addr = new char[pFormalType->size];
                memcpy(addr, Pop()->__addr, pFormalType->size);
                Push(addr);
                pFormalId->runstackItem = TOS();
            } else {

                //--Range check an integer or enumeration
                //--formal parameter.
                RangeCheck(pFormalType, TOS()->__int);
                pFormalId->runstackItem = TOS();
            }
        }
    }
}

void TExecutor::ExecuteRETURN(TSymtabNode *pRoutine) {

    ExecuteAssignment(pRoutine);
    GoTo(pRoutine->defn.routine.returnMarker);

    GetToken();
}

