field("race_stats_table")
write(file("generated/races.bin"))
field("role_stats_table")
write(file("generated/roles.bin"))
field("weapons_stats_table")
write(file("generated/weapons.bin"))
field("armors_stats_table")
write(file("generated/armors.bin"))
field("helments_stats_table")
write(file("generated/helments.bin"))

image_helper("torch", image("../images/torch_16x16.png", 16, 16, 0, true))

-- Tiles (use automatic mipmapping) --
tiles,frames,width,height = image({
	filename = "../images/tiles_32x32.png",
	width = 32,
	height = 32,
	rawtiles = true,
})
raycast_helper("tilesheet", false, {
	["32"] = tiles,
	["16"] = image_resize(tiles, width, height, 16, 16),
	["8"] = image_resize(tiles, width, height, 8, 8),
	["4"] = image_resize(tiles, width, height, 4, 4),
})



local script = require "test_dungeon_maps"