from string import Template


def boundsToStruct(bounds):
    params = [int(item.strip()) for item in bounds.split(',')]
    return "{{.x = {}, .y = {}, .w = {}, .h = {}}}".format(*params)


field = ""
fields = {}

template_string = ""

with open("assets.atlas", 'r') as f:
    while line := f.readline():
        line = line.strip()
        if line.startswith("bounds:") and field != "":
            fields[field] = boundsToStruct(line[7:])
        else:
            field = line

with open("template.c", 'r') as tm:
    template_string = tm.read()

template = Template(template_string)
result = template.substitute(fields)

with open("result.c", 'w') as out:
    out.write(result)
