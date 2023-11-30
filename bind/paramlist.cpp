#include <babble>

#include <OpenImageIO/imagebuf.h>

BBL_MODULE(oiio) {

    bbl::Class<OIIO::ParamValue>()
        .ctor(bbl::Class<OIIO::ParamValue>::Ctor<>(), "default")
        .ctor(bbl::Class<OIIO::ParamValue>::Ctor<const OIIO::ustring &, OIIO::TypeDesc, int, const void *, bool>("_name", "_type", "_nvalues", "_value", "_copy"), "ctor_01")
        .ctor(bbl::Class<OIIO::ParamValue>::Ctor<const OIIO::ustring &, OIIO::TypeDesc, int, OIIO::ParamValue::Interp, const void *, bool>("_name", "_type", "_nvalues", "_interp", "_value", "_copy"), "ctor_02")
        // .ctor(bbl::Class<OIIO::ParamValue>::Ctor<string_view, TypeDesc, int, const void *, bool>("_name", "_type", "_nvalues", "_value", "_copy"), "ctor_03")
        // .ctor(bbl::Class<OIIO::ParamValue>::Ctor<string_view, TypeDesc, int, Interp, const void *, bool>("_name", "_type", "_nvalues", "_interp", "_value", "_copy"), "ctor_04")
        // .ctor(bbl::Class<OIIO::ParamValue>::Ctor<string_view, int>("_name", "value"), "ctor_05")
        // .ctor(bbl::Class<OIIO::ParamValue>::Ctor<string_view, float>("_name", "value"), "ctor_06")
        // .ctor(bbl::Class<OIIO::ParamValue>::Ctor<string_view, ustring>("_name", "value"), "ctor_07")
        // .ctor(bbl::Class<OIIO::ParamValue>::Ctor<string_view, string_view>("_name", "value"), "ctor_08")
        // .ctor(bbl::Class<OIIO::ParamValue>::Ctor<string_view, TypeDesc, string_view>("_name", "type", "value"), "ctor_09")
        .ctor(bbl::Class<OIIO::ParamValue>::Ctor<const OIIO::ParamValue &, bool>("p", "_copy"), "ctor_10")
        .m((void (OIIO::ParamValue::*)(OIIO::ustring, OIIO::TypeDesc, int, OIIO::ParamValue::Interp, const void *, bool))
            &OIIO::ParamValue::init, "init_00")
        .m((void (OIIO::ParamValue::*)(OIIO::ustring, OIIO::TypeDesc, int, const void *, bool))
            &OIIO::ParamValue::init, "init_01")
        // .m((void (OIIO::ParamValue::*)(string_view, OIIO::TypeDesc, int, const void *, bool))
        //     &OIIO::ParamValue::init, "init_02")
        // .m((void (OIIO::ParamValue::*)(string_view, OIIO::TypeDesc, int, OIIO::ParamValue::Interp, const void *, bool))
        //     &OIIO::ParamValue::init, "init_03")
        .m((const OIIO::ParamValue & (OIIO::ParamValue::*)(const OIIO::ParamValue &))
            &OIIO::ParamValue::operator=, "op_assign_00")
        .m((const OIIO::ParamValue & (OIIO::ParamValue::*)(OIIO::ParamValue &&))
            &OIIO::ParamValue::operator=, "op_assign_01")
        .m(&OIIO::ParamValue::name)
        .m(&OIIO::ParamValue::uname)
        .m(&OIIO::ParamValue::type)
        .m(&OIIO::ParamValue::nvalues)
        .m(&OIIO::ParamValue::data)
        .m(&OIIO::ParamValue::datasize)
        .m((OIIO::ParamValue::Interp (OIIO::ParamValue::*)() const)
            &OIIO::ParamValue::interp, "interp_00")
        .m((void (OIIO::ParamValue::*)(OIIO::ParamValue::Interp))
            &OIIO::ParamValue::interp, "interp_01")
        .m(&OIIO::ParamValue::is_nonlocal)
        /** TODO: instantiate this template
        .m(&OIIO::ParamValue::get)
        */
        .m(&OIIO::ParamValue::get_int)
        .m(&OIIO::ParamValue::get_int_indexed)
        .m(&OIIO::ParamValue::get_float)
        .m(&OIIO::ParamValue::get_float_indexed)
        .m(&OIIO::ParamValue::get_string)
        .m(&OIIO::ParamValue::get_string_indexed)
        .m(&OIIO::ParamValue::get_ustring)
        .m(&OIIO::ParamValue::get_ustring_indexed)
    ;

    // bbl::Class<OIIO::ParamValue::(unnamed union at C:\Users\alanglands\packages\oiio\2.3.16.0\80e249bbcb53f8a3bc3602645377e9f10521481a\include\OpenImageIO\paramlist.h:215:5)>()
    //     .value_type()
    //     .f(&OIIO::ParamValue::(anonymous union)::localval)
    //     .f(&OIIO::ParamValue::(anonymous union)::ptr)
    //     .ctor(bbl::Class<OIIO::ParamValue::(unnamed union at C:\Users\alanglands\packages\oiio\2.3.16.0\80e249bbcb53f8a3bc3602645377e9f10521481a\include\OpenImageIO\paramlist.h:215:5)>::Ctor<>(), "default")
    // ;

    bbl::Class<OIIO::ParamValueList>()
        .ctor(bbl::Class<OIIO::ParamValueList>::Ctor<>(), "default")
        .m(&OIIO::ParamValueList::grow)
        // .m((iterator (OIIO::ParamValueList::*)(string_view, OIIO::TypeDesc, bool))
        //     &OIIO::ParamValueList::find, "find_00")
        // .m((iterator (OIIO::ParamValueList::*)(OIIO::ustring, OIIO::TypeDesc, bool))
        //     &OIIO::ParamValueList::find, "find_01")
        // .m((const_iterator (OIIO::ParamValueList::*)(string_view, OIIO::TypeDesc, bool) const)
        //     &OIIO::ParamValueList::find, "find_02")
        // .m((const_iterator (OIIO::ParamValueList::*)(OIIO::ustring, OIIO::TypeDesc, bool) const)
        //     &OIIO::ParamValueList::find, "find_03")
        // .m((ParamValue * (OIIO::ParamValueList::*)(string_view, OIIO::TypeDesc, bool))
        //     &OIIO::ParamValueList::find_pv, "find_pv_00")
        // .m((const OIIO::ParamValue * (OIIO::ParamValueList::*)(string_view, OIIO::TypeDesc, bool) const)
        //     &OIIO::ParamValueList::find_pv, "find_pv_01")
        .m(&OIIO::ParamValueList::get_int)
        .m(&OIIO::ParamValueList::get_float)
        .m(&OIIO::ParamValueList::get_string)
        .m(&OIIO::ParamValueList::get_ustring)
        .m(&OIIO::ParamValueList::remove)
        .m(&OIIO::ParamValueList::contains)
        .m((void (OIIO::ParamValueList::*)(const OIIO::ParamValue &, bool))
            &OIIO::ParamValueList::add_or_replace, "add_or_replace_00")
        // .m((void (OIIO::ParamValueList::*)(ParamValue &&, bool))
        //     &OIIO::ParamValueList::add_or_replace, "add_or_replace_01")
        // .m((void (OIIO::ParamValueList::*)(string_view, OIIO::TypeDesc, int, const void *))
        //     &OIIO::ParamValueList::attribute, "attribute_00")
        // .m((void (OIIO::ParamValueList::*)(string_view, OIIO::TypeDesc, const void *))
        //     &OIIO::ParamValueList::attribute, "attribute_01")
        // .m((void (OIIO::ParamValueList::*)(string_view, OIIO::TypeDesc, string_view))
        //     &OIIO::ParamValueList::attribute, "attribute_02")
        // .m((void (OIIO::ParamValueList::*)(string_view, int))
        //     &OIIO::ParamValueList::attribute, "attribute_03")
        // .m((void (OIIO::ParamValueList::*)(string_view, unsigned int))
        //     &OIIO::ParamValueList::attribute, "attribute_04")
        // .m((void (OIIO::ParamValueList::*)(string_view, float))
        //     &OIIO::ParamValueList::attribute, "attribute_05")
        // .m((void (OIIO::ParamValueList::*)(string_view, string_view))
        //     &OIIO::ParamValueList::attribute, "attribute_06")
        .m(&OIIO::ParamValueList::getattributetype)
        // .m((bool (OIIO::ParamValueList::*)(string_view, OIIO::TypeDesc, void *, bool) const)
        //     &OIIO::ParamValueList::getattribute, "getattribute_00")
        // .m((bool (OIIO::ParamValueList::*)(string_view, std::string &, bool) const)
        //     &OIIO::ParamValueList::getattribute, "getattribute_01")
        // .m((bool (OIIO::ParamValueList::*)(string_view, int, OIIO::TypeDesc, void *, bool) const)
        //     &OIIO::ParamValueList::getattribute_indexed, "getattribute_indexed_00")
        // .m((bool (OIIO::ParamValueList::*)(string_view, int, std::string &, bool) const)
        //     &OIIO::ParamValueList::getattribute_indexed, "getattribute_indexed_01")
        .m(&OIIO::ParamValueList::sort)
        .m(&OIIO::ParamValueList::merge)
        .m(&OIIO::ParamValueList::free)
        // .m((ParamValue & (OIIO::ParamValueList::*)(int))
        //     &OIIO::ParamValueList::operator[], "op_index_00")
        // .m((const OIIO::ParamValue & (OIIO::ParamValueList::*)(int) const)
        //     &OIIO::ParamValueList::operator[], "op_index_01")
        // .m((AttrDelegate<const OIIO::ParamValueList> (OIIO::ParamValueList::*)(string_view) const)
        //     &OIIO::ParamValueList::operator[], "op_index_02")
        // .m((AttrDelegate<ParamValueList> (OIIO::ParamValueList::*)(string_view))
        //     &OIIO::ParamValueList::operator[], "op_index_03")
        // .m((ParamValueList & (OIIO::ParamValueList::*)(const OIIO::ParamValueList &))
        //     &OIIO::ParamValueList::operator=, "op_assign_00")
        // .m((ParamValueList & (OIIO::ParamValueList::*)(ParamValueList &&))
        //     &OIIO::ParamValueList::operator=, "op_assign_01")
    ;


}