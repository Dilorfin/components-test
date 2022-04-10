file(
	GLOB_RECURSE TicTacToeSourses
	"*.[hc]pp"
	"*.[hc]"
)

ct_add_example(TicTacToe "${TicTacToeSourses}")
