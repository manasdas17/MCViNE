import mcvine
import mccomponents.pyre_support
from mcni.pyre_support.Instrument import Instrument as base
class Instrument(base):
  class Inventory(base.Inventory):
    import pyre.inventory
    from mcni.pyre_support import facility, componentfactory as component
    source = facility('source', default = component('sources', 'SNS_source', supplier = 'mcstas2' )('source' ) )
    core_vessel_insert = facility('core_vessel_insert', default = component('optics', 'Collimator_linear', supplier = 'mcstas2' )('core_vessel_insert' ) )
    start_shutter_insert = facility('start_shutter_insert', default = component('optics', 'Slit', supplier = 'mcstas2' )('start_shutter_insert' ) )
    end_shutter_insert = facility('end_shutter_insert', default = component('optics', 'Slit', supplier = 'mcstas2' )('end_shutter_insert' ) )
    L_monitor1 = facility('L_monitor1', default = component('monitors', 'L_monitor', supplier = 'mcstas2' )('L_monitor1' ) )
    bulk_shield_insert1 = facility('bulk_shield_insert1', default = component('optics', 'Guide', supplier = 'mcstas2' )('bulk_shield_insert1' ) )
    bulk_shield_insert2 = facility('bulk_shield_insert2', default = component('optics', 'Guide', supplier = 'mcstas2' )('bulk_shield_insert2' ) )
    L_monitor2 = facility('L_monitor2', default = component('monitors', 'L_monitor', supplier = 'mcstas2' )('L_monitor2' ) )
    transition_guide1 = facility('transition_guide1', default = component('optics', 'Guide', supplier = 'mcstas2' )('transition_guide1' ) )
    transition_guide2 = facility('transition_guide2', default = component('optics', 'Guide', supplier = 'mcstas2' )('transition_guide2' ) )
    transition_guide3 = facility('transition_guide3', default = component('optics', 'Guide', supplier = 'mcstas2' )('transition_guide3' ) )
    L_monitor3 = facility('L_monitor3', default = component('monitors', 'L_monitor', supplier = 'mcstas2' )('L_monitor3' ) )
    bandwidth_chopper = facility('bandwidth_chopper', default = component('optics', 'DiskChopper', supplier = 'mcstas2' )('bandwidth_chopper' ) )
    curved_guide1 = facility('curved_guide1', default = component('optics', 'Guide', supplier = 'mcstas2' )('curved_guide1' ) )
    curved_guide2 = facility('curved_guide2', default = component('optics', 'Guide', supplier = 'mcstas2' )('curved_guide2' ) )
    curved_guide3 = facility('curved_guide3', default = component('optics', 'Guide', supplier = 'mcstas2' )('curved_guide3' ) )
    curved_guide4 = facility('curved_guide4', default = component('optics', 'Guide', supplier = 'mcstas2' )('curved_guide4' ) )
    curved_guide5 = facility('curved_guide5', default = component('optics', 'Guide', supplier = 'mcstas2' )('curved_guide5' ) )
    curved_guide6 = facility('curved_guide6', default = component('optics', 'Guide', supplier = 'mcstas2' )('curved_guide6' ) )
    L_monitor4 = facility('L_monitor4', default = component('monitors', 'L_monitor', supplier = 'mcstas2' )('L_monitor4' ) )
    curved_guide7 = facility('curved_guide7', default = component('optics', 'Guide', supplier = 'mcstas2' )('curved_guide7' ) )
    curved_guide8 = facility('curved_guide8', default = component('optics', 'Guide', supplier = 'mcstas2' )('curved_guide8' ) )
    curved_guide9 = facility('curved_guide9', default = component('optics', 'Guide', supplier = 'mcstas2' )('curved_guide9' ) )
    curved_guide10 = facility('curved_guide10', default = component('optics', 'Guide', supplier = 'mcstas2' )('curved_guide10' ) )
    curved_guide11 = facility('curved_guide11', default = component('optics', 'Guide', supplier = 'mcstas2' )('curved_guide11' ) )
    curved_guide12 = facility('curved_guide12', default = component('optics', 'Guide', supplier = 'mcstas2' )('curved_guide12' ) )
    curved_guide13 = facility('curved_guide13', default = component('optics', 'Guide', supplier = 'mcstas2' )('curved_guide13' ) )
    curved_guide14 = facility('curved_guide14', default = component('optics', 'Guide', supplier = 'mcstas2' )('curved_guide14' ) )
    curved_guide15 = facility('curved_guide15', default = component('optics', 'Guide', supplier = 'mcstas2' )('curved_guide15' ) )
    curved_guide16 = facility('curved_guide16', default = component('optics', 'Guide', supplier = 'mcstas2' )('curved_guide16' ) )
    curved_guide17 = facility('curved_guide17', default = component('optics', 'Guide', supplier = 'mcstas2' )('curved_guide17' ) )
    curved_guide18 = facility('curved_guide18', default = component('optics', 'Guide', supplier = 'mcstas2' )('curved_guide18' ) )
    curved_guide19 = facility('curved_guide19', default = component('optics', 'Guide', supplier = 'mcstas2' )('curved_guide19' ) )
    curved_guide20 = facility('curved_guide20', default = component('optics', 'Guide', supplier = 'mcstas2' )('curved_guide20' ) )
    curved_guide21 = facility('curved_guide21', default = component('optics', 'Guide', supplier = 'mcstas2' )('curved_guide21' ) )
    curved_guide22 = facility('curved_guide22', default = component('optics', 'Guide', supplier = 'mcstas2' )('curved_guide22' ) )
    curved_guide23 = facility('curved_guide23', default = component('optics', 'Guide', supplier = 'mcstas2' )('curved_guide23' ) )
    curved_guide24 = facility('curved_guide24', default = component('optics', 'Guide', supplier = 'mcstas2' )('curved_guide24' ) )
    curved_guide25 = facility('curved_guide25', default = component('optics', 'Guide', supplier = 'mcstas2' )('curved_guide25' ) )
    curved_guide26 = facility('curved_guide26', default = component('optics', 'Guide', supplier = 'mcstas2' )('curved_guide26' ) )
    curved_guide27 = facility('curved_guide27', default = component('optics', 'Guide', supplier = 'mcstas2' )('curved_guide27' ) )
    curved_guide28 = facility('curved_guide28', default = component('optics', 'Guide', supplier = 'mcstas2' )('curved_guide28' ) )
    curved_guide29 = facility('curved_guide29', default = component('optics', 'Guide', supplier = 'mcstas2' )('curved_guide29' ) )
    curved_guide30 = facility('curved_guide30', default = component('optics', 'Guide', supplier = 'mcstas2' )('curved_guide30' ) )
    curved_guide31 = facility('curved_guide31', default = component('optics', 'Guide', supplier = 'mcstas2' )('curved_guide31' ) )
    curved_guide32 = facility('curved_guide32', default = component('optics', 'Guide', supplier = 'mcstas2' )('curved_guide32' ) )
    curved_guide33 = facility('curved_guide33', default = component('optics', 'Guide', supplier = 'mcstas2' )('curved_guide33' ) )
    curved_guide34 = facility('curved_guide34', default = component('optics', 'Guide', supplier = 'mcstas2' )('curved_guide34' ) )
    curved_guide35 = facility('curved_guide35', default = component('optics', 'Guide', supplier = 'mcstas2' )('curved_guide35' ) )
    curved_guide36 = facility('curved_guide36', default = component('optics', 'Guide', supplier = 'mcstas2' )('curved_guide36' ) )
    curved_guide37 = facility('curved_guide37', default = component('optics', 'Guide', supplier = 'mcstas2' )('curved_guide37' ) )
    curved_guide38 = facility('curved_guide38', default = component('optics', 'Guide', supplier = 'mcstas2' )('curved_guide38' ) )
    curved_guide39 = facility('curved_guide39', default = component('optics', 'Guide', supplier = 'mcstas2' )('curved_guide39' ) )
    curved_guide40 = facility('curved_guide40', default = component('optics', 'Guide', supplier = 'mcstas2' )('curved_guide40' ) )
    curved_guide41 = facility('curved_guide41', default = component('optics', 'Guide', supplier = 'mcstas2' )('curved_guide41' ) )
    curved_guide42 = facility('curved_guide42', default = component('optics', 'Guide', supplier = 'mcstas2' )('curved_guide42' ) )
    L_monitor5 = facility('L_monitor5', default = component('monitors', 'L_monitor', supplier = 'mcstas2' )('L_monitor5' ) )
    straight_section1 = facility('straight_section1', default = component('optics', 'Guide', supplier = 'mcstas2' )('straight_section1' ) )
    straight_section2 = facility('straight_section2', default = component('optics', 'Guide', supplier = 'mcstas2' )('straight_section2' ) )
    straight_section3 = facility('straight_section3', default = component('optics', 'Guide', supplier = 'mcstas2' )('straight_section3' ) )
    L_monitor6 = facility('L_monitor6', default = component('monitors', 'L_monitor', supplier = 'mcstas2' )('L_monitor6' ) )
    VTG_Slit = facility('VTG_Slit', default = component('optics', 'Slit', supplier = 'mcstas2' )('VTG_Slit' ) )
    vertical_tapered_guide1 = facility('vertical_tapered_guide1', default = component('optics', 'Guide_gravity', supplier = 'mcstas2' )('vertical_tapered_guide1' ) )
    vertical_tapered_guide2 = facility('vertical_tapered_guide2', default = component('optics', 'Guide_gravity', supplier = 'mcstas2' )('vertical_tapered_guide2' ) )
    vertical_tapered_guide3 = facility('vertical_tapered_guide3', default = component('optics', 'Guide_gravity', supplier = 'mcstas2' )('vertical_tapered_guide3' ) )
    vertical_tapered_guide4 = facility('vertical_tapered_guide4', default = component('optics', 'Guide_gravity', supplier = 'mcstas2' )('vertical_tapered_guide4' ) )
    vertical_tapered_guide5 = facility('vertical_tapered_guide5', default = component('optics', 'Guide_gravity', supplier = 'mcstas2' )('vertical_tapered_guide5' ) )
    vertical_tapered_guide6 = facility('vertical_tapered_guide6', default = component('optics', 'Guide_gravity', supplier = 'mcstas2' )('vertical_tapered_guide6' ) )
    vertical_tapered_guide7 = facility('vertical_tapered_guide7', default = component('optics', 'Guide_gravity', supplier = 'mcstas2' )('vertical_tapered_guide7' ) )
    vertical_tapered_guide8 = facility('vertical_tapered_guide8', default = component('optics', 'Guide_gravity', supplier = 'mcstas2' )('vertical_tapered_guide8' ) )
    vertical_tapered_guide9 = facility('vertical_tapered_guide9', default = component('optics', 'Guide_gravity', supplier = 'mcstas2' )('vertical_tapered_guide9' ) )
    vertical_tapered_guide10 = facility('vertical_tapered_guide10', default = component('optics', 'Guide_gravity', supplier = 'mcstas2' )('vertical_tapered_guide10' ) )
    vertical_tapered_guide11 = facility('vertical_tapered_guide11', default = component('optics', 'Guide_gravity', supplier = 'mcstas2' )('vertical_tapered_guide11' ) )
    vertical_tapered_guide12 = facility('vertical_tapered_guide12', default = component('optics', 'Guide_gravity', supplier = 'mcstas2' )('vertical_tapered_guide12' ) )
    vertical_tapered_guide13 = facility('vertical_tapered_guide13', default = component('optics', 'Guide_gravity', supplier = 'mcstas2' )('vertical_tapered_guide13' ) )
    vertical_tapered_guide14 = facility('vertical_tapered_guide14', default = component('optics', 'Guide_gravity', supplier = 'mcstas2' )('vertical_tapered_guide14' ) )
    vertical_tapered_guide15 = facility('vertical_tapered_guide15', default = component('optics', 'Guide_gravity', supplier = 'mcstas2' )('vertical_tapered_guide15' ) )
    L_monitor7 = facility('L_monitor7', default = component('monitors', 'L_monitor', supplier = 'mcstas2' )('L_monitor7' ) )
    TG_Slit = facility('TG_Slit', default = component('optics', 'Slit', supplier = 'mcstas2' )('TG_Slit' ) )
    tapered_guide1 = facility('tapered_guide1', default = component('optics', 'Guide_gravity', supplier = 'mcstas2' )('tapered_guide1' ) )
    tapered_guide2 = facility('tapered_guide2', default = component('optics', 'Guide_gravity', supplier = 'mcstas2' )('tapered_guide2' ) )
    tapered_guide3 = facility('tapered_guide3', default = component('optics', 'Guide_gravity', supplier = 'mcstas2' )('tapered_guide3' ) )
    tapered_guide4 = facility('tapered_guide4', default = component('optics', 'Guide_gravity', supplier = 'mcstas2' )('tapered_guide4' ) )
    tapered_guide5 = facility('tapered_guide5', default = component('optics', 'Guide_gravity', supplier = 'mcstas2' )('tapered_guide5' ) )
    tapered_guide6 = facility('tapered_guide6', default = component('optics', 'Guide_gravity', supplier = 'mcstas2' )('tapered_guide6' ) )
    tapered_guide7 = facility('tapered_guide7', default = component('optics', 'Guide_gravity', supplier = 'mcstas2' )('tapered_guide7' ) )
    tapered_guide8 = facility('tapered_guide8', default = component('optics', 'Guide_gravity', supplier = 'mcstas2' )('tapered_guide8' ) )
    tapered_guide9 = facility('tapered_guide9', default = component('optics', 'Guide_gravity', supplier = 'mcstas2' )('tapered_guide9' ) )
    L_monitor8 = facility('L_monitor8', default = component('monitors', 'L_monitor', supplier = 'mcstas2' )('L_monitor8' ) )
    L_monitor9 = facility('L_monitor9', default = component('monitors', 'L_monitor', supplier = 'mcstas2' )('L_monitor9' ) )
    L_monitor10 = facility('L_monitor10', default = component('monitors', 'L_monitor', supplier = 'mcstas2' )('L_monitor10' ) )
    psd_sample_position = facility('psd_sample_position', default = component('monitors', 'PSD_monitor', supplier = 'mcstas2' )('psd_sample_position' ) )
    psd_xscan_L = facility('psd_xscan_L', default = component('monitors', 'Monitor_nD', supplier = 'mcstas2' )('psd_xscan_L' ) )
    psd_yscan_L = facility('psd_yscan_L', default = component('monitors', 'Monitor_nD', supplier = 'mcstas2' )('psd_yscan_L' ) )
  def _defaults(self):
    base._defaults(self)
    geometer = self.inventory.geometer

if __name__ == "__main__":
  app = Instrument( "InstrFCL5NBB" )
  app.run()
