// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#define PROPELLER_FORWARD_DECLARE(p_class) class p_class;
#define PROPELLER_FORWARD_DECLARE_STRUCT(p_class) struct p_class;

#define PROPELLER_FORWARD_DECLARE_1(p_name1, p_class) namespace p_name1 { class p_class; }
#define PROPELLER_FORWARD_DECLARE_2(p_name1, p_name2, p_class) namespace p_name1 { namespace p_name2 { class p_class; } }
#define PROPELLER_FORWARD_DECLARE_3(p_name1, p_name2, p_name3, p_class) namespace p_name1 { namespace p_name2 { namespace p_name3 { class p_class; } } }

#define PROPELLER_FORWARD_DECLARE_STRUCT_1(p_name1, p_class) namespace p_name1 { struct p_class; }
#define PROPELLER_FORWARD_DECLARE_STRUCT_2(p_name1, p_name2, p_class) namespace p_name1 { namespace p_name2 { struct p_class; } }
#define PROPELLER_FORWARD_DECLARE_STRUCT_3(p_name1, p_name2, p_name3, p_class) namespace p_name1 { namespace p_name2 { namespace p_name3 { struct p_class; } } }
