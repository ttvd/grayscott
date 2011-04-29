/*
 *  framebuffer.cpp
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

#include "framebuffer.h"

namespace Comp5201Project
{
	//--


	//--
	FrameBuffer::FrameBuffer(int width, int height, QObject* parent) :
	QObject(parent),
	m_width(width),
	m_height(height),
	m_fbo(0),
	m_tex_color(0),
	m_tex_depthstencil(0)
	{
		// [rad] Color attachment.
		glGenTextures(1, &m_tex_color);
		glBindTexture(GL_TEXTURE_2D, m_tex_color);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 

		glBindTexture(GL_TEXTURE_2D, 0);

		// [rad] Depth attachment.
		glGenTextures(1, &m_tex_depthstencil);
		glBindTexture(GL_TEXTURE_2D, m_tex_depthstencil);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, m_width, m_height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
		glBindTexture(GL_TEXTURE_2D, 0);

		// [rad] FBO
		glGenFramebuffersEXT(1, &m_fbo);
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_fbo);
        glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, m_tex_color, 0);
        glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, m_tex_depthstencil, 0);

        GLenum render_targets[] = {GL_COLOR_ATTACHMENT0_EXT};
		glDrawBuffers(1, render_targets);

		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	}


	//--
	FrameBuffer::~FrameBuffer()
	{
		if(m_tex_color)
		{
			glDeleteTextures(1, &m_tex_color);
		}

		if(m_tex_depthstencil)
		{
			glDeleteTextures(1, &m_tex_depthstencil);
		}

		if(m_fbo)
		{
			glDeleteFramebuffersEXT(1, &m_fbo);
		}
	}


	//--
	void 
	FrameBuffer::resize(int width, int height)
	{
		m_width = width;
		m_height = height;
		
		// [rad] Delete associated resources.

		if(m_tex_color)
		{
			glDeleteTextures(1, &m_tex_color);
		}

		if(m_tex_depthstencil)
		{
			glDeleteTextures(1, &m_tex_depthstencil);
		}

		if(m_fbo)
		{
			glDeleteFramebuffersEXT(1, &m_fbo);
		}

		// [rad] Color attachment.
		glGenTextures(1, &m_tex_color);
		glBindTexture(GL_TEXTURE_2D, m_tex_color);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
		glBindTexture(GL_TEXTURE_2D, 0);

		// [rad] Depth attachment.
		glGenTextures(1, &m_tex_depthstencil);
		glBindTexture(GL_TEXTURE_2D, m_tex_depthstencil);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, m_width, m_height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
		glBindTexture(GL_TEXTURE_2D, 0);

		// [rad] FBO
		glGenFramebuffersEXT(1, &m_fbo);
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_fbo);
        glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, m_tex_color, 0);
        glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, m_tex_depthstencil, 0);

        GLenum render_targets[] = {GL_COLOR_ATTACHMENT0_EXT};
		glDrawBuffers(1, render_targets);

		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	}


	//--
	void
	FrameBuffer::bind()
	{
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_fbo);
	}


	//--
	void
	FrameBuffer::release()
	{
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	}


	//--
	void
	FrameBuffer::bindColor()
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_tex_color);
	}


	//--
	void
	FrameBuffer::releaseColor()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_TEXTURE_2D);
	}


	//--
	void
	FrameBuffer::bindDepth()
	{
		glBindTexture(GL_TEXTURE_2D, m_tex_depthstencil);
		glEnable(GL_TEXTURE_2D);
	}


	//--
	void
	FrameBuffer::releaseDepth()
	{
		glDisable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
	}


	//--
	GLuint 
	FrameBuffer::attachmentColor() const
	{
		return(m_tex_color);
	}
}
