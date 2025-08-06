import bpy


class MYADDON_OT_GravityFrag(bpy.types.Operator):
    bl_idname = "myaddon.gravityflag"
    bl_label = "GravityFlag"
    bl_description = "flagManager"
    bl_options = {"REGISTER", "UNDO"}


    def execute(self, context):
        obj = context.object
        obj["gravity_Flag"] = True
        return {"FINISHED"}


class OBJECT_PT_GravityFlag(bpy.types.Panel):
    """ 重力フラグパネル """

    bl_idname = "OBJECT_PT_gravityflag"
    bl_label = "GravityFlagPanel"
    bl_space_type = "PROPERTIES" 
    bl_region_type = "WINDOW"
    bl_context = "object"

    def draw(self,context):
        obj = context.object

        if "gravity_Flag" in obj:
            self.layout.prop(obj, '["gravity_Flag"]', text="重力有true")
        else:
            self.layout.operator(MYADDON_OT_GravityFrag.bl_idname)
            