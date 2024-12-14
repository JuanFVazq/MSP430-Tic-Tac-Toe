	.text
	.global assemblyFunction

assemblyFunction:
	;;  Save the return address
	PUSH    R1

	;;  Call the calledFunction
	CALL    #calledFunction

	;;  Restore the return address
	POP     R1

	;;  Return from function
	RET
