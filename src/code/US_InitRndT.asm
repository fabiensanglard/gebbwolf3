
;=================================================
;
;
; void US_InitRndT (boolean randomize)
; Init table based RND generator
; if randomize is false, the counter is set to 0
;
;
;=================================================


PROC	US_InitRndT randomize:word

	uses	si,di
	public	US_InitRndT

	mov	ax,SEG rndtable
	mov	es,ax

	mov	ax,[randomize]
	or	ax,ax
	jne	@@timeit		;if randomize is true, really random

	mov	dx,0			;set to a definite value
	jmp	@@setit

@@timeit:
	mov	ah,2ch
	int	21h			;GetSystemTime
	and	dx,0ffh

@@setit:
	mov	[es:rndindex],dx
	ret

ENDP