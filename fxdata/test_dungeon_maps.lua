test_dungeon = {
   {
   8,8,
   1,1,1,1,1,1,1,1,
   1,1,1,1,1,1,1,1,
   1,1,1,1,1,1,1,1,
   1,2,2,2,1,1,1,1,
   1,2,1,2,1,1,1,1,
   1,2,1,2,2,1,4,1,
   1,2,3,2,2,2,9,1,
   1,1,1,1,1,1,1,1},
   {
   8,8,
   1,1,1,1,1,1,1,1,
   1,1,1,1,1,1,1,1,
   1,1,1,1,1,1,1,1,
   1,1,2,2,2,2,2,1,
   1,2,2,1,2,2,2,1,
   1,2,9,1,1,3,1,1,
   1,1,4,1,1,1,1,1,
   1,1,1,1,1,1,1,1}
   }
   
   offsets = {}
   totaloffset = 0
   field("test_dungeon")
   for i,d in ipairs(test_dungeon) do
      offsets[i] = totaloffset
      totaloffset = totaloffset + write(bytes(d))
   end
   field("test_dungeon_offsets")
   write(bytes(offsets, "uint16"))
   
   test_dungeon_raycast = {
   {
   8,8,
   1,1,1,1,1,1,1,1,
   1,1,1,1,1,1,1,1,
   1,1,1,1,1,1,1,1,
   1,1,1,1,0,0,0,1,
   4,4,4,1,0,1,0,1,
   4,0,4,0,0,3,0,1,
   4,0,0,0,0,0,0,1,
   1,1,1,1,3,3,3,1},
   {
   8,8,
   1,1,1,1,1,1,1,1,
   1,1,1,1,1,1,1,1,
   1,1,1,1,1,1,1,1,
   1,0,0,0,0,0,1,1,
   1,0,0,0,1,0,0,1,
   1,3,0,3,4,0,0,1,
   1,3,3,3,4,0,4,1,
   1,1,1,1,4,4,4,1}
   }
   
   offsets = {}
   totaloffset = 0
   field("test_dungeon_raycast")
   for i,d in ipairs(test_dungeon_raycast) do
      offsets[i] = totaloffset
      totaloffset = totaloffset + write(bytes(d))
   end
   field("test_dungeon_raycast_offsets")
   write(bytes(offsets, "uint16"))
   