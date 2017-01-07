typedef struct	statestruct
{
	boolean	rotate;
	int		shapenum;	// Sprite to render on screen
	int		tictime;    // How long stay in that state
	void	(*think) (),(*action) ();
	struct	statestruct	*next;
} statetype;