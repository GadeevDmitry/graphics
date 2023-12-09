#include <stdio.h>
#include "window/filter_param_window.h"

//==================================================================================================

const vec2d filter_param_window_t::content_ld_off(20, 20);
const vec2d filter_param_window_t::content_ru_off(20, 50);

const double filter_param_window_t::edit_box_off   = 10;
const double filter_param_window_t::edit_box_width = 200;

const double filter_param_window_t::string_height = 30;
const double filter_param_window_t::hollow_height = 10;

//==================================================================================================

bool apply_button_controller_t::on_mouse_press(widget_t *handle, const eventable::mouse_context_t &context, const MOUSE_BUTTON_TYPE &btn)
{
    const uint64_t param_num = param_wnd.edit_boxes.size;
    double *param_new_values = new double[param_num];

    for (uint64_t param_cnt = 0; param_cnt < param_num; ++param_cnt)
    {
        const char *str_val = (**(edit_box_t **) array_get(&param_wnd.edit_boxes, param_cnt)).get_string();
        double      dbl_val = strtod(str_val, NULL);

        param_new_values[param_cnt] = dbl_val;
    }

    param_wnd.filter->set_params(plugin::Array<double>(param_num, param_new_values));
    delete[] param_new_values;

    param_wnd.status = widget_t::WIDGET_CLOSED;
    param_wnd.update_ancestral_status(widget_t::WIDGET_ACTIVATED);

    return true;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

filter_param_window_t::filter_param_window_t(event_manager_t &event_manager_, const char *wnd_name, FilterI *filter_):
modal_window_t       (event_manager_, window_t::Blue_theme, wnd_name),
apply_btn_controller (*this),
apply_btn            (new label_button_t(apply_btn_controller, "Apply", 20)),
filter               (filter_),
edit_boxes           ()
{}

//--------------------------------------------------------------------------------------------------

filter_param_window_t::filter_param_window_t(event_manager_t &event_manager_, const rectangle_t &root_enclosing_, const char *wnd_name, FilterI *filter_):
modal_window_t       (event_manager_, window_t::Blue_theme, wnd_name),
apply_btn_controller (*this),
apply_btn            (new label_button_t(apply_btn_controller, "Apply", 20)),
filter               (filter_),
edit_boxes           ()
{
    create(root_enclosing_, filter_);
}

//--------------------------------------------------------------------------------------------------

void filter_param_window_t::create(const rectangle_t &root_enclosing, FilterI *filter_)
{
    filter = (filter_ == nullptr) ? filter : filter_;
    LOG_VERIFY(filter != nullptr, (void) 0);

    plugin::Array<const char *> param_names = filter->get_param_names();
    const uint64_t              param_num   = param_names.size;

    double name_width = 0;
    for (uint64_t cnt = param_num; cnt > 0; cnt--)
    {
        // reverse order for right create_params() work
        label_t *param_name = new label_t(param_names.data[param_num - cnt], 20);
        param_name->text_rel_off = vec2d(0, 0);
        param_name->background   = color;
        param_name->text.color   = color_t::White;

        register_subwidget(widget_proxy_t(param_name));
        name_width = std::max(name_width, param_name->text.get_string_size().x);
    }
    name_width += 5;

    vec2d wnd_size(
        content_ld_off.x + name_width + edit_box_off + edit_box_width                  + content_ru_off.x,
        content_ld_off.y + param_num * string_height + (param_num - 1) * hollow_height + content_ru_off.y);
    wnd_size += vec2d(0, window_t::header_menu_height);

    LOG_ASSERT(root_enclosing.get_size().x > wnd_size.x);
    LOG_ASSERT(root_enclosing.get_size().y > wnd_size.y);

    enclosing = rectangle_t(
        (root_enclosing.ld_corner + (root_enclosing.get_size() - wnd_size) / 2).floor(),
        wnd_size.x, wnd_size.y);

    create_params(param_num, name_width);
    create_apply_btn();

    modal_window_t::create(enclosing);
}

//--------------------------------------------------------------------------------------------------

void filter_param_window_t::create_params(const size_t param_num, const double param_name_width)
{
    vec2d param_i_name_off     = vec2d(0, window_t::header_menu_height) + content_ld_off;
    vec2d param_i_edit_box_off = param_i_name_off + vec2d(param_name_width + edit_box_off, 0);

    widget_proxy_t *param_i_name_proxy = (widget_proxy_t *) list_front(&subwidgets);
    for (size_t param_i = 0; param_i < param_num; ++param_i)
    {
        LOG_ASSERT(param_i_name_proxy->is_internal);
        label_t *param_i_name = (label_t *) param_i_name_proxy->internal;

        param_i_name->enclosing = rectangle_t(enclosing.ld_corner + param_i_name_off, param_name_width, string_height);
        param_i_name->create_texture();

        param_i_name_off += vec2d(0, string_height + hollow_height);
        param_i_name_proxy = (widget_proxy_t *) list_next(param_i_name_proxy);
    }

    array_ctor(&edit_boxes, param_num, sizeof(edit_box_t *));

    plugin::Array<double> param_values = filter->get_params();
    LOG_ASSERT(param_values.size == param_num);

    for (size_t param_i = 0; param_i < param_num; ++param_i)
    {
        edit_box_t *param_i_edit_box = new edit_box_t(20);
        array_set(&edit_boxes, param_i, &param_i_edit_box);

        param_i_edit_box->enclosing = rectangle_t(enclosing.ld_corner + param_i_edit_box_off, edit_box_width, string_height);
        param_i_edit_box->create_texture();

        double param_i_value = param_values.data[param_i];
        char   param_i_value_str[10] = "";
        snprintf(param_i_value_str, 9, "%.3lf", param_i_value);
        param_i_edit_box->set_string(param_i_value_str);

        param_i_edit_box_off += vec2d(0, string_height + hollow_height);
        register_subwidget(widget_proxy_t(param_i_edit_box));
    }
}

//--------------------------------------------------------------------------------------------------

void filter_param_window_t::create_apply_btn()
{
    const vec2d btn_size(60, 30);
    const vec2d lu_off  ((enclosing.get_size().x - btn_size.x) / 2, -10 - btn_size.y);

    apply_btn->enclosing    = rectangle_t(enclosing.lu_corner() + lu_off, btn_size.x, btn_size.y);
    apply_btn->text_rel_off = vec2d(5, 0);
    apply_btn->background   = color;
    apply_btn->text.color   = color_t::White;

    apply_btn->create_texture();

    register_subwidget(widget_proxy_t(apply_btn));
}
