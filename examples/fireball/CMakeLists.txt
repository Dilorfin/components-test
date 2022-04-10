file(
	GLOB_RECURSE FireballSourses
	"*.[hc]pp"
	"*.[hc]"
)

ct_add_example(Fireball "${FireballSourses}")
