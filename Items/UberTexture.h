#ifndef UBERTEXTURE_H
#define UBERTEXTURE_H

#include <QSGTexture>
#include <QtGui/qopengl.h>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <memory>
#include "_2RealDatatypes.h"

namespace Uber {
class UberTexture : public QSGTexture
{
    Q_OBJECT
public:
    UberTexture();
    ~UberTexture();
    void    setData( std::shared_ptr< const _2Real::Image>  data );
    void    bind();
    bool hasAlphaChannel() const { return m_has_alpha; }
     bool hasMipmaps() const { return m_has_mipmaps; }
    int     textureId() const;
    QSize textureSize() const { return m_texture_size; }
signals:

public slots:
protected:
    std::shared_ptr< const _2Real::Image> m_Data;
    GLuint  m_texture_id;
    QSize   m_texture_size;
    QRectF m_texture_rect;
    uint m_has_alpha : 1;
    uint m_has_mipmaps : 1;
    uint m_dirty_texture : 1;
    uint m_dirty_bind_options : 1;
    uint m_owns_texture : 1;
    uint m_mipmaps_generated : 1;
    uint m_retain_image: 1;

};
}

#endif // UBERTEXTURE_H
