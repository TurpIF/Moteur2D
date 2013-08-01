#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/gl.h>
#include <cstddef>
#include <string>

class Texture {
    public:
        typedef GLuint       id_type;
        typedef std::string filename_type;

    protected:
        typedef GLuint  dim_type;
        typedef GLenum  format_type;
        typedef GLint   internal_format_type;
        typedef GLubyte texel_type;

    public:
        struct file_buffer {
            typedef unsigned char byte;
            typedef std::size_t size_type;

            filename_type   name;
            byte *          data;
            size_type       length;
            size_type       offset;
        };

        Texture(Texture &&) = default;
        Texture(Texture const &) = default;
        Texture & operator=(Texture const &) = default;

        Texture(filename_type const &);

        id_type const & id() const;
        dim_type const & width() const;
        dim_type const & height() const;

    protected:
        struct gl_texture_type {
            dim_type                width;
            dim_type                height;
            format_type             format;
            internal_format_type    internal_format;
            texel_type *            texels;
        };

        static file_buffer read_file(filename_type const &);
        static gl_texture_type const read_png(file_buffer);

    protected:
        id_type     _id;
        dim_type    _width;
        dim_type    _height;
};

#endif
