import bpy


class MYADDON_OT_TerrainFlag(bpy.types.Operator):
    bl_idname = "myaddon.terrainflag"
    bl_label = "terrainFlag"
    bl_description = "flagManager"
    bl_options = {"REGISTER", "UNDO"}


    def execute(self, context):
        obj = context.object
        obj["terrain_Flag"] = True
        return {"FINISHED"}


class OBJECT_PT_TerrainFlag(bpy.types.Panel):
    """ 地形当たり判定フラグパネル """

    bl_idname = "OBJECT_PT_terrainflag"
    bl_label = "TerrainFlagPanel"
    bl_space_type = "PROPERTIES" 
    bl_region_type = "WINDOW"
    bl_context = "object"

    def draw(self,context):
        obj = context.object

        if "terrain_Flag" in obj:
            self.layout.prop(obj, '["terrain_Flag"]', text="地形有true")
        else:
            self.layout.operator(MYADDON_OT_TerrainFlag.bl_idname)
            