#include <babble>

#include <OpenImageIO/imagebuf.h>

BBL_MODULE(oiio) {

    bbl::Class<OIIO::ROI>()
        .value_type()
        .f(&OIIO::ROI::xbegin)
        .f(&OIIO::ROI::xend)
        .f(&OIIO::ROI::ybegin)
        .f(&OIIO::ROI::yend)
        .f(&OIIO::ROI::zbegin)
        .f(&OIIO::ROI::zend)
        .f(&OIIO::ROI::chbegin)
        .f(&OIIO::ROI::chend)
        .ctor(bbl::Class<OIIO::ROI>::Ctor<>(), "default")
        .ctor(bbl::Class<OIIO::ROI>::Ctor<int, int, int, int, int, int, int, int>("xbegin", "xend", "ybegin", "yend", "zbegin", "zend", "chbegin", "chend"), "with_dimensions")
        .m(&OIIO::ROI::defined)
        .m(&OIIO::ROI::width)
        .m(&OIIO::ROI::height)
        .m(&OIIO::ROI::depth)
        .m(&OIIO::ROI::nchannels)
        .m(&OIIO::ROI::npixels)
        .m(&OIIO::ROI::All)
        .m((bool (OIIO::ROI::*)(int, int, int, int) const)
            &OIIO::ROI::contains, "contains_region")
        .m((bool (OIIO::ROI::*)(const OIIO::ROI &) const)
            &OIIO::ROI::contains, "contains")
    ;

    bbl::Class<OIIO::ImageSpec>()
        .ctor(bbl::Class<OIIO::ImageSpec>::Ctor<OIIO::TypeDesc>("format"), "new")
        // .ctor(bbl::Class<OIIO::ImageSpec>::Ctor<OIIO::string_view>("format"), "with_named_type")
        .ctor(bbl::Class<OIIO::ImageSpec>::Ctor<int, int, int, OIIO::TypeDesc>("xres", "yres", "nchans", "fmt"), "with_dimensions")
        // .ctor(bbl::Class<OIIO::ImageSpec>::Ctor<int, int, int, string_view>("xres", "yres", "nchans", "fmt"), "ctor_03")
        .ctor(bbl::Class<OIIO::ImageSpec>::Ctor<const OIIO::ROI &, OIIO::TypeDesc>("roi", "fmt"), "with_region")
        // .ctor(bbl::Class<OIIO::ImageSpec>::Ctor<const OIIO::ROI &, string_view>("roi", "fmt"), "ctor_05")
        .m((void (OIIO::ImageSpec::*)(OIIO::TypeDesc))
            &OIIO::ImageSpec::set_format, "set_format")
        .m(bbl::Wrap((void (OIIO::ImageSpec::*)(OIIO::string_view))
            &OIIO::ImageSpec::set_format, [](OIIO::ImageSpec& _this, char const* fmt) -> void {
                _this.set_format(fmt);
            }), "set_format_with_typename")
        .m(&OIIO::ImageSpec::default_channel_names)
        .m((size_t (OIIO::ImageSpec::*)() const)
            &OIIO::ImageSpec::channel_bytes, "channel_bytes_00")
        .m((size_t (OIIO::ImageSpec::*)(int, bool) const)
            &OIIO::ImageSpec::channel_bytes, "channel_bytes_01")
        .m((size_t (OIIO::ImageSpec::*)(bool) const)
            &OIIO::ImageSpec::pixel_bytes, "pixel_bytes_00")
        .m((size_t (OIIO::ImageSpec::*)(int, int, bool) const)
            &OIIO::ImageSpec::pixel_bytes, "pixel_bytes_01")
        .m(&OIIO::ImageSpec::scanline_bytes)
        .m(&OIIO::ImageSpec::tile_pixels)
        .m(&OIIO::ImageSpec::tile_bytes)
        .m(&OIIO::ImageSpec::image_pixels)
        .m(&OIIO::ImageSpec::image_bytes)
        .m(&OIIO::ImageSpec::size_t_safe)
        .m((void (*)(OIIO::stride_t &, OIIO::stride_t &, OIIO::stride_t &, OIIO::stride_t, int, int, int))
            &OIIO::ImageSpec::auto_stride, "auto_stride_00")
        .m((void (*)(OIIO::stride_t &, OIIO::stride_t &, OIIO::stride_t &, OIIO::TypeDesc, int, int, int))
            &OIIO::ImageSpec::auto_stride, "auto_stride_01")
        .m((void (*)(OIIO::stride_t &, OIIO::TypeDesc, int))
            &OIIO::ImageSpec::auto_stride, "auto_stride_02")
        .m(bbl::Wrap((void (OIIO::ImageSpec::*)(OIIO::string_view, OIIO::TypeDesc, const void *))
            &OIIO::ImageSpec::attribute, 
            [](OIIO::ImageSpec& _this, char const* name, OIIO::TypeDesc type, void const* data) -> void {
                _this.attribute(name, type, data);
            }), "attribute"
        )
        .m(
            bbl::Wrap(&OIIO::ImageSpec::erase_attribute,
            [](OIIO::ImageSpec& _this, char const* name, OIIO::TypeDesc search_type, bool casesensitive) -> void {
                _this.erase_attribute(name, search_type, casesensitive);
            }
        ))
        .m(bbl::Wrap((OIIO::ParamValue * (OIIO::ImageSpec::*)(OIIO::string_view, OIIO::TypeDesc, bool))
            &OIIO::ImageSpec::find_attribute, 
            [](OIIO::ImageSpec& _this, char const* name, OIIO::TypeDesc type, bool casesensitive) -> OIIO::ParamValue* {
                return _this.find_attribute(name, type, casesensitive);
            }), "find_attribute")
        .m(bbl::Wrap((OIIO::ParamValue const* (OIIO::ImageSpec::*)(OIIO::string_view, OIIO::TypeDesc, bool) const)
            &OIIO::ImageSpec::find_attribute, 
            [](OIIO::ImageSpec const& _this, char const* name, OIIO::TypeDesc type, bool casesensitive) -> OIIO::ParamValue const* {
                return _this.find_attribute(name, type, casesensitive);
            }), "find_attribute_const")
        .m(bbl::Wrap(&OIIO::ImageSpec::getattributetype,
            [](OIIO::ImageSpec const& _this, char const* name, bool casesensitive) -> OIIO::TypeDesc {
                return _this.getattributetype(name, casesensitive);
            }))
        .m(bbl::Wrap(&OIIO::ImageSpec::getattribute, [](OIIO::ImageSpec const& _this, char const* name, OIIO::TypeDesc type, void* value, bool casesensitive) -> bool {
            return _this.getattribute(name, type, value, casesensitive);
        }))
        .m(&OIIO::ImageSpec::metadata_val)
        .m(&OIIO::ImageSpec::serialize)
        .m(&OIIO::ImageSpec::to_xml)
        .m(&OIIO::ImageSpec::from_xml)
        .m(bbl::Wrap(&OIIO::ImageSpec::decode_compression_metadata, [](OIIO::ImageSpec const& _this, char const* name, int defaultqual, char const** compression, long long* compression_len, int* compression_quality) -> void {
            auto result = _this.decode_compression_metadata(name, defaultqual);
            *compression = result.first.c_str();
            *compression_len = result.first.size();
            *compression_quality = result.second;
        }))
        .m(&OIIO::ImageSpec::valid_tile_range)
        .m(&OIIO::ImageSpec::channelformat)
        .m(bbl::Wrap(&OIIO::ImageSpec::channel_name, [](OIIO::ImageSpec const& _this, int chan, char const** name, long long* len) -> void {
            auto sv = _this.channel_name(chan);
            *name = sv.c_str();
            *len = sv.size();
        }))
        .m(&OIIO::ImageSpec::get_channelformats)
        .m(bbl::Wrap(&OIIO::ImageSpec::channelindex, [](OIIO::ImageSpec const& _this, char const* name) -> int {
            return _this.channelindex(name);
        }))
        .m(&OIIO::ImageSpec::roi)
        .m(&OIIO::ImageSpec::roi_full)
        .m(&OIIO::ImageSpec::set_roi)
        .m(&OIIO::ImageSpec::set_roi_full)
        .m(&OIIO::ImageSpec::copy_dimensions)
        .m(&OIIO::ImageSpec::undefined)
    ;

    bbl::Enum<OIIO::ImageSpec::SerialFormat>();
    bbl::Enum<OIIO::ImageSpec::SerialVerbose>();

    bbl::Class<OIIO::ImageInput::unique_ptr>("ImageInputPtr")
        .smartptr_to<OIIO::ImageInput>()
    ;

    bbl::Class<OIIO::ImageInput>()
        .m(bbl::Wrap((OIIO::ImageInput::unique_ptr (*)(const std::string &, const OIIO::ImageSpec *, OIIO::Filesystem::IOProxy *))
            &OIIO::ImageInput::open, [](char const* filename, OIIO::ImageSpec const* spec, OIIO::Filesystem::IOProxy* ioproxy) -> OIIO::ImageInput::unique_ptr {
                return OIIO::ImageInput::open(filename, spec, ioproxy);
            }), "open_with_ioproxy")
        .m(bbl::Wrap((bool (OIIO::ImageInput::*)(const std::string &, OIIO::ImageSpec &))
            &OIIO::ImageInput::open, [](OIIO::ImageInput& _this, char const* filename, OIIO::ImageSpec& spec) -> bool {
                return _this.open(filename, spec);
            }), "open")
        .m(bbl::Wrap((bool (OIIO::ImageInput::*)(const std::string &, OIIO::ImageSpec &, const OIIO::ImageSpec &))
            &OIIO::ImageInput::open, [](OIIO::ImageInput& _this, char const* filename, OIIO::ImageSpec& spec, OIIO::ImageSpec const& config) -> bool {
                return _this.open(filename, spec, config);
            }), "open_with_config")
        .m(bbl::Wrap((OIIO::ImageInput::unique_ptr (*)(OIIO::string_view, bool, const OIIO::ImageSpec *, OIIO::Filesystem::IOProxy *, OIIO::string_view))
            &OIIO::ImageInput::create, [](char const* filename, bool doopen, OIIO::ImageSpec const* config, OIIO::Filesystem::IOProxy* ioproxy, char const* plugin_searchpath) -> OIIO::ImageInput::unique_ptr {
                return OIIO::ImageInput::create(filename, doopen, config, ioproxy, plugin_searchpath);
            }), "create_with_ioproxy")
        .m(&OIIO::ImageInput::destroy)
        .m(&OIIO::ImageInput::format_name)
        .m(bbl::Wrap(&OIIO::ImageInput::supports, [](OIIO::ImageInput const& _this, char const* feature) -> int {
            return _this.supports(feature);
        }))
        .m(bbl::Wrap((bool (OIIO::ImageInput::*)(const std::string &) const)
            &OIIO::ImageInput::valid_file, [](OIIO::ImageInput const& _this, char const* filename) -> bool {
                return _this.valid_file(filename);
            }), "valid_file")
        .m((const OIIO::ImageSpec & (OIIO::ImageInput::*)() const)
            &OIIO::ImageInput::spec, "spec")
        .m((OIIO::ImageSpec (OIIO::ImageInput::*)(int, int))
            &OIIO::ImageInput::spec, "spec_from_subimage")
        .m(&OIIO::ImageInput::spec_dimensions)
        .m(&OIIO::ImageInput::get_thumbnail)
        .m(&OIIO::ImageInput::close)
        .m(&OIIO::ImageInput::current_subimage)
        .m(&OIIO::ImageInput::current_miplevel)
        .m((bool (OIIO::ImageInput::*)(int, int))
            &OIIO::ImageInput::seek_subimage, "seek_subimage_00")
        .m((bool (OIIO::ImageInput::*)(int, int, OIIO::ImageSpec &))
            &OIIO::ImageInput::seek_subimage, "seek_subimage_01")
        .m((bool (OIIO::ImageInput::*)(int, OIIO::ImageSpec &))
            &OIIO::ImageInput::seek_subimage, "seek_subimage_02")
        .m((bool (OIIO::ImageInput::*)(int, int, OIIO::TypeDesc, void *, OIIO::stride_t))
            &OIIO::ImageInput::read_scanline, "read_scanline_00")
        .m((bool (OIIO::ImageInput::*)(int, int, float *))
            &OIIO::ImageInput::read_scanline, "read_scanline_01")
        .m((bool (OIIO::ImageInput::*)(int, int, int, int, int, int, int, OIIO::TypeDesc, void *, OIIO::stride_t, OIIO::stride_t))
            &OIIO::ImageInput::read_scanlines, "read_scanlines_00")
        .m((bool (OIIO::ImageInput::*)(int, int, int, OIIO::TypeDesc, void *, OIIO::stride_t, OIIO::stride_t))
            &OIIO::ImageInput::read_scanlines, "read_scanlines_01")
        .m((bool (OIIO::ImageInput::*)(int, int, int, int, int, OIIO::TypeDesc, void *, OIIO::stride_t, OIIO::stride_t))
            &OIIO::ImageInput::read_scanlines, "read_scanlines_02")
        .m((bool (OIIO::ImageInput::*)(int, int, int, OIIO::TypeDesc, void *, OIIO::stride_t, OIIO::stride_t, OIIO::stride_t))
            &OIIO::ImageInput::read_tile, "read_tile_00")
        .m((bool (OIIO::ImageInput::*)(int, int, int, float *))
            &OIIO::ImageInput::read_tile, "read_tile_01")
        .m((bool (OIIO::ImageInput::*)(int, int, int, int, int, int, int, int, int, int, OIIO::TypeDesc, void *, OIIO::stride_t, OIIO::stride_t, OIIO::stride_t))
            &OIIO::ImageInput::read_tiles, "read_tiles_00")
        .m((bool (OIIO::ImageInput::*)(int, int, int, int, int, int, OIIO::TypeDesc, void *, OIIO::stride_t, OIIO::stride_t, OIIO::stride_t))
            &OIIO::ImageInput::read_tiles, "read_tiles_01")
        .m((bool (OIIO::ImageInput::*)(int, int, int, int, int, int, int, int, OIIO::TypeDesc, void *, OIIO::stride_t, OIIO::stride_t, OIIO::stride_t))
            &OIIO::ImageInput::read_tiles, "read_tiles_02")
        // .m((bool (OIIO::ImageInput::*)(int, int, int, int, OIIO::TypeDesc, void *, OIIO::stride_t, OIIO::stride_t, OIIO::stride_t, ProgressCallback, void *))
        //     &OIIO::ImageInput::read_image, "read_image_00")
        // .m((bool (OIIO::ImageInput::*)(OIIO::TypeDesc, void *, OIIO::stride_t, OIIO::stride_t, OIIO::stride_t, ProgressCallback, void *))
        //     &OIIO::ImageInput::read_image, "read_image_01")
        // .m((bool (OIIO::ImageInput::*)(int, int, OIIO::TypeDesc, void *, OIIO::stride_t, OIIO::stride_t, OIIO::stride_t, ProgressCallback, void *))
        //     &OIIO::ImageInput::read_image, "read_image_02")
        .m((bool (OIIO::ImageInput::*)(float *))
            &OIIO::ImageInput::read_image, "read_image_03")
        .m((bool (OIIO::ImageInput::*)(int, int, int, int, int, int, int, OIIO::DeepData &))
            &OIIO::ImageInput::read_native_deep_scanlines, "read_native_deep_scanlines_00")
        .m((bool (OIIO::ImageInput::*)(int, int, int, int, int, OIIO::DeepData &))
            &OIIO::ImageInput::read_native_deep_scanlines, "read_native_deep_scanlines_01")
        .m((bool (OIIO::ImageInput::*)(int, int, int, int, int, int, int, int, int, int, OIIO::DeepData &))
            &OIIO::ImageInput::read_native_deep_tiles, "read_native_deep_tiles_00")
        .m((bool (OIIO::ImageInput::*)(int, int, int, int, int, int, int, int, OIIO::DeepData &))
            &OIIO::ImageInput::read_native_deep_tiles, "read_native_deep_tiles_01")
        .m((bool (OIIO::ImageInput::*)(int, int, OIIO::DeepData &))
            &OIIO::ImageInput::read_native_deep_image, "read_native_deep_image_00")
        .m((bool (OIIO::ImageInput::*)(OIIO::DeepData &))
            &OIIO::ImageInput::read_native_deep_image, "read_native_deep_image_01")
        .m(&OIIO::ImageInput::read_native_scanline)
        .m((bool (OIIO::ImageInput::*)(int, int, int, int, int, void *))
            &OIIO::ImageInput::read_native_scanlines, "read_native_scanlines_00")
        .m((bool (OIIO::ImageInput::*)(int, int, int, int, int, int, int, void *))
            &OIIO::ImageInput::read_native_scanlines, "read_native_scanlines_01")
        .m(&OIIO::ImageInput::read_native_tile)
        .m((bool (OIIO::ImageInput::*)(int, int, int, int, int, int, int, int, void *))
            &OIIO::ImageInput::read_native_tiles, "read_native_tiles_00")
        .m((bool (OIIO::ImageInput::*)(int, int, int, int, int, int, int, int, int, int, void *))
            &OIIO::ImageInput::read_native_tiles, "read_native_tiles_01")
        .m(&OIIO::ImageInput::set_ioproxy)
        .m(&OIIO::ImageInput::has_error)
        .m(&OIIO::ImageInput::geterror)
        .m((void (OIIO::ImageInput::*)(int))
            &OIIO::ImageInput::threads, "threads")
        .m((int (OIIO::ImageInput::*)() const)
            &OIIO::ImageInput::threads, "threads_const")
        .m(&OIIO::ImageInput::lock)
        .m(&OIIO::ImageInput::unlock)
        .m(&OIIO::ImageInput::try_lock)
    ;

    bbl::Class<OIIO::ImageOutput::unique_ptr>("ImageOutputPtr")
        .smartptr_to<OIIO::ImageOutput>()
    ;

    bbl::Class<OIIO::ImageOutput>()
        .m(bbl::Wrap((OIIO::ImageOutput::unique_ptr (*)(OIIO::string_view, OIIO::Filesystem::IOProxy *, OIIO::string_view))
            &OIIO::ImageOutput::create, [](char const* filename, OIIO::Filesystem::IOProxy* ioproxy, char const* plugin_searchpath) -> OIIO::ImageOutput::unique_ptr {
                return OIIO::ImageOutput::create(filename, ioproxy, plugin_searchpath);
            }), "create")
        .m(&OIIO::ImageOutput::destroy)
        .m(&OIIO::ImageOutput::format_name)
        .m(bbl::Wrap(&OIIO::ImageOutput::supports, [](OIIO::ImageOutput const& _this, char const* feature) -> int {
            return _this.supports(feature);
        }))
        .m(bbl::Wrap((bool (OIIO::ImageOutput::*)(const std::string &, const OIIO::ImageSpec &, OIIO::ImageOutput::OpenMode))
            &OIIO::ImageOutput::open, [](OIIO::ImageOutput& _this, char const* filename, OIIO::ImageSpec const& spec, OIIO::ImageOutput::OpenMode openmode) -> bool {
                return _this.open(filename, spec, openmode);
            }), "open")
        .m(bbl::Wrap((bool (OIIO::ImageOutput::*)(const std::string &, int, const OIIO::ImageSpec *))
            &OIIO::ImageOutput::open, [](OIIO::ImageOutput& _this, char const* filename, int num_subimages, OIIO::ImageSpec const* specs) -> bool {
                return _this.open(filename, num_subimages, specs);
            }), "open_multi_subimage")
        .m(&OIIO::ImageOutput::spec)
        .m(&OIIO::ImageOutput::close)
        .m(&OIIO::ImageOutput::write_scanline)
        .m(&OIIO::ImageOutput::write_scanlines)
        .m(&OIIO::ImageOutput::write_tile)
        .m(&OIIO::ImageOutput::write_tiles)
        .m(&OIIO::ImageOutput::write_rectangle)
        // TODO: ProgressCallback
        // .m(&OIIO::ImageOutput::write_image)
        .m(&OIIO::ImageOutput::write_deep_scanlines)
        .m(&OIIO::ImageOutput::write_deep_tiles)
        .m(&OIIO::ImageOutput::write_deep_image)
        .m(&OIIO::ImageOutput::set_thumbnail)
        .m(&OIIO::ImageOutput::copy_image)
        .m(&OIIO::ImageOutput::set_ioproxy)
        .m(&OIIO::ImageOutput::has_error)
        .m(&OIIO::ImageOutput::geterror)
        .m((void (OIIO::ImageOutput::*)(int))
            &OIIO::ImageOutput::threads, "setthreads")
        .m((int (OIIO::ImageOutput::*)() const)
            &OIIO::ImageOutput::threads, "getthreads")
    ;

    bbl::Enum<OIIO::ImageOutput::OpenMode>();

    bbl::fn(&OIIO::roi_union);

    bbl::fn(&OIIO::roi_intersection);

    bbl::ClassIncomplete<OIIO::Filesystem::IOProxy>();

}
