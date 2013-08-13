#include "UberTexture.h"
#include "../system/System.h"
namespace Uber {
    UberTexture::UberTexture()
    :QSGTexture()
    , m_texture_id(0)
    , m_has_alpha(false)
    , m_has_mipmaps(false)
    , m_dirty_bind_options(false)
    , m_owns_texture(true)
    , m_mipmaps_generated(false)
    , m_retain_image(false)
    , m_Data(nullptr)
    {

    }

    UberTexture::~UberTexture()
    {
        if (m_texture_id && m_owns_texture)
            glDeleteTextures(1, &m_texture_id);
    }

    void UberTexture::setData( std::shared_ptr< const _2Real::Image> data )
    {
        m_Data = data;

        m_has_alpha = false;
        m_dirty_texture = true;
        m_dirty_bind_options = true;
    }

    void UberTexture::bind()
    {
        if (!m_dirty_texture) {
            glBindTexture(GL_TEXTURE_2D, m_texture_id);
            if (m_has_mipmaps && !m_mipmaps_generated) {
                QOpenGLContext *ctx = System::getInstance()->getWindow()->openglContext();
                ctx->functions()->glGenerateMipmap(GL_TEXTURE_2D);
                m_mipmaps_generated = true;
            }
            updateBindOptions(m_dirty_bind_options);
            m_dirty_bind_options = false;
            return;
        }

        m_dirty_texture = false;

        if (!m_Data) {
            if (m_texture_id && m_owns_texture) {
                glDeleteTextures(1, &m_texture_id);
            }
            m_texture_id = 0;
            m_texture_size = QSize();
            m_has_mipmaps = false;
            m_has_alpha = false;
            return;
        }

        if (m_texture_id == 0)
            glGenTextures(1, &m_texture_id);
        glBindTexture(GL_TEXTURE_2D, m_texture_id);
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );



        updateBindOptions(m_dirty_bind_options);

        GLenum externalFormat = GL_RGBA;
        GLenum internalFormat = GL_RGBA;


        GLenum uploadFormat = GL_RGBA;
        GLenum uploadType = GL_UNSIGNED_BYTE;

        const unsigned int w = m_Data->getWidth();
        const unsigned int h = m_Data->getHeight();
        const _2Real::Image::ChannelOrder channels = m_Data->getChannelOrder();
        const _2Real::Image::Datatype type = m_Data->getDatatype();

        // note that i ignore the bgr vs rgb thing for testing
        switch ( channels.getNumberOfChannels() )
        {
        case 4:
            uploadFormat = GL_RGBA;
            break;
        case 3:
            uploadFormat = GL_RGB;
            break;
        default:
            // for some reason GL_RG is not recognized ( probably need glew )
            uploadFormat = GL_RED;
            break;
        }

        switch ( type.getCode() )
        {
        case _2Real::Image::Datatype::UINT8:
            uploadType = GL_UNSIGNED_BYTE;
            break;
        case _2Real::Image::Datatype::UINT16:
            uploadType = GL_UNSIGNED_SHORT;
            break;
        case _2Real::Image::Datatype::UINT32:
            uploadType = GL_UNSIGNED_INT;
            break;
        case _2Real::Image::Datatype::INT8:
            uploadType = GL_BYTE;
            break;
        case _2Real::Image::Datatype::INT16:
            uploadType = GL_SHORT;
            break;
        case _2Real::Image::Datatype::INT32:
            uploadType = GL_INT;
            break;
        case _2Real::Image::Datatype::FLOAT32:
            uploadType = GL_FLOAT;
            break;
        case _2Real::Image::Datatype::FLOAT64:
            // in this case,assume float - it won't work properly, but then, nothing will
            uploadType = GL_UNSIGNED_BYTE;
            break;
        default:
            uploadType = GL_UNSIGNED_BYTE;
            break;
        }

        if ( w != m_texture_size.width() || h != m_texture_size.height() )
        {
            m_texture_size = QSize(m_Data->getWidth(), m_Data->getHeight());
            glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, uploadFormat, uploadType, ( const GLvoid * )m_Data->getPixels() );
        }
        else
        {
            glTexSubImage2D( GL_TEXTURE_2D, 0, 0, 0, w, h, uploadFormat, uploadType, ( const GLvoid * )m_Data->getPixels() );
        }
        if (m_has_mipmaps) {
            QOpenGLContext *ctx = System::getInstance()->getWindow()->openglContext();
            ctx->functions()->glGenerateMipmap(GL_TEXTURE_2D);
            m_mipmaps_generated = true;
        }
        m_texture_rect = QRectF(0, 0, 1, 1);

        m_dirty_bind_options = false;
        if (!m_retain_image)
            m_Data = nullptr;
    }

    int UberTexture::textureId() const
    {
        if (m_dirty_texture) {
            if (!m_Data) {
                // The actual texture and id will be updated/deleted in a later bind()
                // or ~QSGPlainTexture so just keep it minimal here.
                return 0;
            } else if (m_texture_id == 0){
                // Generate a texture id for use later and return it.
                glGenTextures(1, &const_cast<UberTexture *>(this)->m_texture_id);
                return m_texture_id;
            }
        }
        return m_texture_id;
    }
}
