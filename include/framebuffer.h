/*
 *  framebuffer.h
 *  Gray-Scott Reaction Diffusion system.
 *
 *  Framebuffer wrapper.
 *
 *  Created by radix on 04/29/11.
 *  Copyright Mykola Konyk, <mykola@konyk.org>, 2011.
 *  
 *  This code is under Microsoft Reciprocal License (Ms-RL)
 *  Please see http://www.opensource.org/licenses/ms-rl.html
 *
 *  Important points about the license (from Ms-RL):
 *
 *  [A] For any file you distribute that contains code from the software (in source code or binary format), you must provide 
 *  recipients the source code to that file along with a copy of this license, which license will govern that file. 
 *  You may license other files that are entirely your own work and do not contain code from the software under any terms 
 *  you choose.
 *
 *  [B] No Trademark License- This license does not grant you rights to use any contributors' name, logo, or trademarks.
 *
 *  [C] If you bring a patent claim against any contributor over patents that you claim are infringed by the software, your 
 *  patent license from such contributor to the software ends automatically.
 *
 *  [D] If you distribute any portion of the software, you must retain all copyright, patent, trademark, and attribution notices 
 *  that are present in the software.
 *
 *  [E] If you distribute any portion of the software in source code form, you may do so only under this license by including a
 *  complete copy of this license with your distribution. If you distribute any portion of the software in compiled or object 
 *  code form, you may only do so under a license that complies with this license.
 *
 *  [F] The software is licensed "as-is." You bear the risk of using it. The contributors give no express warranties, guarantees 
 *  or conditions. You may have additional consumer rights under your local laws which this license cannot change. To the extent 
 *  permitted under your local laws, the contributors exclude the implied warranties of merchantability, fitness for a particular 
 *  purpose and non-infringement.
 *
 */

#if !defined(COMP_5201_PROJECT_CONCENTRATIONV_H)
#define COMP_5201_PROJECT_CONCENTRATIONV_H

#include <QtCore/QObject>
#include <QtCore/QtGlobal>

#if defined(Q_OS_WIN)
	#include <GL/glew.h>
#elif defined(Q_OS_MAC)
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#endif

namespace Comp5201Project
{
	class FrameBuffer : public QObject
	{
		Q_OBJECT	

		public:

			FrameBuffer(int width, int height, QObject* parent);
			virtual ~FrameBuffer();

		public:

			void bind();
			void release();

			void bindColor();
			void releaseColor();

			void bindDepth();
			void releaseDepth();

			GLuint attachmentColor() const;

			void resize(int width, int height);

		protected:

			int m_width;
			int m_height;

			GLuint m_fbo;

			GLuint m_tex_color;
			GLuint m_tex_depthstencil;
	};	
}

#endif //!defined(COMP_5201_PROJECT_RENDER2D_H)
