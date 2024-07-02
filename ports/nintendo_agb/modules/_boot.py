import uos
import gba

tmp_romfs = None
tmp_fatfs = None

try:
    tmp_romfs = gba.ROMFS()
    tmp_fatfs = uos.VfsFat(tmp_romfs)
    uos.mount(tmp_fatfs, '/')
except:
    print("Error: No valid ROMFS found")
finally:
    del tmp_romfs
    del tmp_fatfs
    
    del uos
    del gba
