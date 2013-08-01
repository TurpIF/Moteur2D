#include "texture.h"

#include <png.h>
#include <fstream>
#include <algorithm>
#include <stdexcept>

Texture::Texture(filename_type const & __f):
    _id(0),
    _width(0),
    _height(0)
{
    try {
        gl_texture_type t(read_png(read_file(__f)));
        _width = t.width;
        _height = t.height;

        glGenTextures(1, &_id);
        glBindTexture(GL_TEXTURE_2D, _id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, t.internal_format, _width, _height,
                0, t.format, GL_UNSIGNED_BYTE, t.texels);

        delete t.texels;
    }
    catch(std::fstream::failure) {
        throw;
    }
    catch(std::bad_alloc) {
        throw;
    }
    catch(std::runtime_error) {
        throw;
    }
}

Texture::id_type const & Texture::id() const {
    return _id;
}

Texture::dim_type const & Texture::width() const {
    return _width;
}

Texture::dim_type const & Texture::height() const {
    return _height;
}

Texture::file_buffer Texture::read_file(filename_type const & __f) {
    file_buffer fb;
    std::fstream file;
    file.exceptions(std::fstream::badbit | std::fstream::failbit);

    try {
        file.open(__f.c_str(), std::fstream::in | std::fstream::binary);
        fb.name = __f;
        file.seekg(0, file.end);
        fb.length = file.tellg();
        fb.offset = 0;
        file.seekg(0, file.beg);
        fb.data = new file_buffer::byte[fb.length];
        file.read(reinterpret_cast<char *>(fb.data), fb.length);
        file.close();
    }
    catch(std::fstream::failure)
    {
        throw;
    }
    catch(std::bad_alloc)
    {
        file.close();
        throw;
    }

    return fb;
}

void png_read_from_mem(png_structp png_ptr,
        png_bytep data,
        png_size_t length) {
    Texture::file_buffer * src = reinterpret_cast<Texture::file_buffer *>(
            png_get_io_ptr(png_ptr));
    std::copy_n(src->data + src->offset, length, data);
    src->offset += length;
}

Texture::gl_texture_type const Texture::read_png(Texture::file_buffer __fb) {
    if(!png_check_sig(__fb.data, 8)) {
        throw std::runtime_error("Impossible to read this PNG.");
    }

    png_structp png_ptr = png_create_read_struct(
            PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if(!png_ptr) {
        throw std::runtime_error("Impossible to create a png_struct struct");
    }

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if(!info_ptr) {
        png_destroy_read_struct(&png_ptr, NULL, NULL);
        throw std::runtime_error("Impossible to create a png_info struct");
    }

    gl_texture_type tex;
    png_bytep * row_pointers = nullptr;

    if(setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        if(tex.texels != nullptr)
            delete [] tex.texels;

        if(row_pointers != nullptr)
            delete [] row_pointers;

        throw std::runtime_error("Impossible to read the PNG");
    }

    png_set_read_fn(png_ptr,
            reinterpret_cast<png_voidp *>(&__fb),
            png_read_from_mem);
    png_read_info(png_ptr, info_ptr);

    int bit_depth = png_get_bit_depth(png_ptr, info_ptr);
    int color_type = png_get_color_type(png_ptr, info_ptr);

    if(color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(png_ptr);
    if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
        png_set_gray_1_2_4_to_8(png_ptr);
    if(png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
        png_set_tRNS_to_alpha(png_ptr);

    if(bit_depth == 16)
        png_set_strip_16(png_ptr);
    else if(bit_depth < 8)
        png_set_packing(png_ptr);

    png_read_update_info(png_ptr, info_ptr);

    png_uint_32 w;
    png_uint_32 h;
    png_get_IHDR(png_ptr, info_ptr, &w, &h,
            &bit_depth, &color_type, NULL, NULL, NULL);

    tex.width = static_cast<dim_type>(w);
    tex.height = static_cast<dim_type>(h);

    switch(color_type) {
        case PNG_COLOR_TYPE_GRAY:
            tex.format = GL_LUMINANCE;
            tex.internal_format = 1;
            break;

        case PNG_COLOR_TYPE_GRAY_ALPHA:
            tex.format = GL_LUMINANCE_ALPHA;
            tex.internal_format = 2;
            break;

        case PNG_COLOR_TYPE_RGB:
            tex.format = GL_RGB;
            tex.internal_format = 3;
            break;

        case PNG_COLOR_TYPE_RGB_ALPHA:
            tex.format = GL_RGBA;
            tex.internal_format = 4;
            break;

        default:
            throw std::runtime_error("Impossible to detect the format.");
            break;
    }

    try {
        tex.texels = new texel_type
            [tex.width * tex.height * tex.internal_format];
        row_pointers = new png_bytep[tex.height];
    }
    catch(std::bad_alloc) {
        throw;
    }

    for(dim_type i = 0; i < tex.height ; i++) {
        row_pointers[i] = static_cast<png_bytep>(tex.texels +
                (tex.height - (i + 1))
                 * tex.width * tex.internal_format);
    }

    png_read_image (png_ptr, row_pointers);
    delete[] row_pointers;
    row_pointers = nullptr;

    png_read_end(png_ptr, NULL);
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

    return tex;
}
