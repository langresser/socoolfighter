/* $Change: 597344 $ */
#ifndef _gl_macro_h_
#define _gl_macro_h_

// redefine gl function
#ifdef glAlphaFunc
#undef glAlphaFunc
#endif 
#define		glAlphaFunc		glAlphaFunc_1
#define		glClearColor		glClearColor_1
#define		glClearDepthf		glClearDepthf_1
#define		glClipPlanef		glClipPlanef_1
#define		glColor4f		glColor4f_1
#define		glDepthRangef		glDepthRangef_1
#define		glFogf		glFogf_1
#define		glFogfv		glFogfv_1
#define		glFrustumf		glFrustumf_1
#define		glGetClipPlanef		glGetClipPlanef_1
#define		glGetFloatv		glGetFloatv_1
#define		glGetLightfv		glGetLightfv_1
#define		glGetMaterialfv		glGetMaterialfv_1
#define		glGetTexEnvfv		glGetTexEnvfv_1
#define		glGetTexParameterfv		glGetTexParameterfv_1
#define		glLightModelf		glLightModelf_1
#define		glLightModelfv		glLightModelfv_1
#define		glLightf		glLightf_1
#define		glLightfv		glLightfv_1
#define		glLineWidth		glLineWidth_1
#define		glLoadMatrixf		glLoadMatrixf_1
#define		glMaterialf		glMaterialf_1
#define		glMaterialfv		glMaterialfv_1
#define		glMultMatrixf		glMultMatrixf_1
#define		glMultiTexCoord4f		glMultiTexCoord4f_1
#define		glNormal3f		glNormal3f_1
#define		glOrthof		glOrthof_1
#define		glPointParameterf		glPointParameterf_1
#define		glPointParameterfv		glPointParameterfv_1
#define		glPointSize		glPointSize_1
#define		glPolygonOffset		glPolygonOffset_1
#define		glRotatef		glRotatef_1
#define		glScalef		glScalef_1
#define		glTexEnvf		glTexEnvf_1
#define		glTexEnvfv		glTexEnvfv_1
#define		glTexParameterf		glTexParameterf_1
#define		glTexParameterfv		glTexParameterfv_1
#define		glTranslatef		glTranslatef_1
#define		glActiveTexture		glActiveTexture_1
#define		glAlphaFuncx		glAlphaFuncx_1
#define		glBindBuffer		glBindBuffer_1
#define		glBindTexture		glBindTexture_1
#define		glBlendFunc		glBlendFunc_1
#define		glBufferData		glBufferData_1
#define		glBufferSubData		glBufferSubData_1
#define		glClear		glClear_1
#define		glClearColorx		glClearColorx_1
#define		glClearDepthx		glClearDepthx_1
#define		glClearStencil		glClearStencil_1
#define		glClientActiveTexture		glClientActiveTexture_1
#define		glClipPlanex		glClipPlanex_1
#define		glColor4ub		glColor4ub_1
#define		glColor4x		glColor4x_1
#define		glColorMask		glColorMask_1
#define		glColorPointer		glColorPointer_1
#define		glCompressedTexImage2D		glCompressedTexImage2D_1
#define		glCompressedTexSubImage2D		glCompressedTexSubImage2D_1
#define		glCopyTexImage2D		glCopyTexImage2D_1
#define		glCopyTexSubImage2D		glCopyTexSubImage2D_1
#define		glCullFace		glCullFace_1
#define		glDeleteBuffers		glDeleteBuffers_1
#define		glDeleteTextures		glDeleteTextures_1
#define		glDepthFunc		glDepthFunc_1
#define		glDepthMask		glDepthMask_1
#define		glDepthRangex		glDepthRangex_1
#define		glDisable		glDisable_1
#define		glDisableClientState		glDisableClientState_1
#define		glDrawArrays		glDrawArrays_1
#define		glDrawElements		glDrawElements_1
#define		glEnable		glEnable_1
#define		glEnableClientState		glEnableClientState_1
#define		glFinish		glFinish_1
#define		glFlush		glFlush_1
#define		glFogx		glFogx_1
#define		glFogxv		glFogxv_1
#define		glFrontFace		glFrontFace_1
#define		glFrustumx		glFrustumx_1
#define		glGetBooleanv		glGetBooleanv_1
#define		glGetBufferParameteriv		glGetBufferParameteriv_1
#define		glGetClipPlanex		glGetClipPlanex_1
#define		glGenBuffers		glGenBuffers_1
#define		glGenTextures		glGenTextures_1
#define		glGetError		glGetError_1
#define		glGetFixedv		glGetFixedv_1
#define		glGetIntegerv		glGetIntegerv_1
#define		glGetLightxv		glGetLightxv_1
#define		glGetMaterialxv		glGetMaterialxv_1
#define		glGetPointerv		glGetPointerv_1
#define		glGetString		glGetString_1
#define		glGetTexEnviv		glGetTexEnviv_1
#define		glGetTexEnvxv		glGetTexEnvxv_1
#define		glGetTexParameteriv		glGetTexParameteriv_1
#define		glGetTexParameterxv		glGetTexParameterxv_1
#define		glHint		glHint_1
#define		glIsBuffer		glIsBuffer_1
#define		glIsEnabled		glIsEnabled_1
#define		glIsTexture		glIsTexture_1
#define		glLightModelx		glLightModelx_1
#define		glLightModelxv		glLightModelxv_1
#define		glLightx		glLightx_1
#define		glLightxv		glLightxv_1
#define		glLineWidthx		glLineWidthx_1
#define		glLoadIdentity		glLoadIdentity_1
#define		glLoadMatrixx		glLoadMatrixx_1
#define		glLogicOp		glLogicOp_1
#define		glMaterialx		glMaterialx_1
#define		glMaterialxv		glMaterialxv_1
#define		glMatrixMode		glMatrixMode_1
#define		glMultMatrixx		glMultMatrixx_1
#define		glMultiTexCoord4x		glMultiTexCoord4x_1
#define		glNormal3x		glNormal3x_1
#define		glNormalPointer		glNormalPointer_1
#define		glOrthox		glOrthox_1
#define		glPixelStorei		glPixelStorei_1
#define		glPointParameterx		glPointParameterx_1
#define		glPointParameterxv		glPointParameterxv_1
#define		glPointSizex		glPointSizex_1
#define		glPolygonOffsetx		glPolygonOffsetx_1
#define		glPopMatrix		glPopMatrix_1
#define		glPushMatrix		glPushMatrix_1
#define		glReadPixels		glReadPixels_1
#define		glRotatex 		glRotatex_1
#define		glSampleCoverage		glSampleCoverage_1
#define		glSampleCoveragex		glSampleCoveragex_1
#define		glScalex		glScalex_1
#define		glScissor		glScissor_1
#define		glShadeModel		glShadeModel_1
#define		glStencilFunc		glStencilFunc_1
#define		glStencilMask		glStencilMask_1
#define		glStencilOp		glStencilOp_1
#define		glTexCoordPointer		glTexCoordPointer_1
#define		glTexEnvi		glTexEnvi_1
#define		glTexEnvx		glTexEnvx_1
#define		glTexEnviv		glTexEnviv_1
#define		glTexEnvxv		glTexEnvxv_1
#define		glTexImage2D		glTexImage2D_1
#define		glTexParameteri		glTexParameteri_1
#define		glTexParameterx		glTexParameterx_1
#define		glTexParameteriv		glTexParameteriv_1
#define		glTexParameterxv		glTexParameterxv_1
#define		glTexSubImage2D		glTexSubImage2D_1
#define		glTranslatex		glTranslatex_1
#define		glVertexPointer		glVertexPointer_1
#define		glViewport		glViewport_1
#define		glPointSizePointerOES glPointSizePointerOES_1
#define		glCurrentPaletteMatrixOES glCurrentPaletteMatrixOES_1
#define		glLoadPaletteFromModelViewMatrixOES glLoadPaletteFromModelViewMatrixOES_1
#define		glMatrixIndexPointerOES glMatrixIndexPointerOES_1
#define		glWeightPointerOES glWeightPointerOES_1

//Start of FBO Functions
#define		glIsRenderbufferOES glIsRenderbufferOES_1
#define		glBindRenderbufferOES glBindRenderbufferOES_1
#define		glDeleteRenderbuffersOES glDeleteRenderbuffersOES_1
#define		glGenRenderbuffersOES glGenRenderbuffersOES_1
#define		glRenderbufferStorageOES glRenderbufferStorageOES_1
#define		glGetRenderbufferParameterivOES glGetRenderbufferParameterivOES_1
#define		glIsFramebufferOES glIsFramebufferOES_1
#define		glBindFramebufferOES glBindFramebufferOES_1
#define		glDeleteFramebuffersOES glDeleteFramebuffersOES_1
#define		glGenFramebuffersOES glGenFramebuffersOES_1
#define		glCheckFramebufferStatusOES glCheckFramebufferStatusOES_1
#define		glFramebufferRenderbufferOES glFramebufferRenderbufferOES_1
#define		glFramebufferTexture2DOES glFramebufferTexture2DOES_1
#define		glGetFramebufferAttachmentParameterivOES glGetFramebufferAttachmentParameterivOES_1
#define		glGenerateMipmapOES glGenerateMipmapOES_1
//End of FBO Functions


#endif // _egl_macro_h_
