//------------------------------------------------------------------------------
// <auto-generated />
//
// This file was automatically generated by SWIG (http://www.swig.org).
// Version 4.0.2
//
// Do not make changes to this file unless you know what you are doing--modify
// the SWIG interface file instead.
//------------------------------------------------------------------------------

namespace Effekseer.swig {

public class GraphicsDevice : global::System.IDisposable {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;
  private bool swigCMemOwnBase;

  internal GraphicsDevice(global::System.IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwnBase = cMemoryOwn;
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(GraphicsDevice obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~GraphicsDevice() {
    Dispose(false);
  }

  public void Dispose() {
    Dispose(true);
    global::System.GC.SuppressFinalize(this);
  }

  protected virtual void Dispose(bool disposing) {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwnBase) {
          swigCMemOwnBase = false;
          EffekseerNativePINVOKE.delete_GraphicsDevice(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
    }
  }

  public void Resize(int width, int height) {
    EffekseerNativePINVOKE.GraphicsDevice_Resize(swigCPtr, width, height);
    if (EffekseerNativePINVOKE.SWIGPendingException.Pending) throw EffekseerNativePINVOKE.SWIGPendingException.Retrieve();
  }

  public void ResetRenderTargets() {
    EffekseerNativePINVOKE.GraphicsDevice_ResetRenderTargets(swigCPtr);
    if (EffekseerNativePINVOKE.SWIGPendingException.Pending) throw EffekseerNativePINVOKE.SWIGPendingException.Retrieve();
  }

  public void ClearColor(byte r, byte g, byte b, byte a) {
    EffekseerNativePINVOKE.GraphicsDevice_ClearColor(swigCPtr, r, g, b, a);
    if (EffekseerNativePINVOKE.SWIGPendingException.Pending) throw EffekseerNativePINVOKE.SWIGPendingException.Retrieve();
  }

  public void Present() {
    EffekseerNativePINVOKE.GraphicsDevice_Present(swigCPtr);
    if (EffekseerNativePINVOKE.SWIGPendingException.Pending) throw EffekseerNativePINVOKE.SWIGPendingException.Retrieve();
  }

  public static GraphicsDevice Create(System.IntPtr handle, int width, int height, bool isSRGBMode, DeviceType deviceType) {
    global::System.IntPtr cPtr = EffekseerNativePINVOKE.GraphicsDevice_Create(handle, width, height, isSRGBMode, (int)deviceType);
    GraphicsDevice ret = (cPtr == global::System.IntPtr.Zero) ? null : new GraphicsDevice(cPtr, true);
    return ret;
  }

  public bool GetIsSRGBMode() {
    bool ret = EffekseerNativePINVOKE.GraphicsDevice_GetIsSRGBMode(swigCPtr);
    if (EffekseerNativePINVOKE.SWIGPendingException.Pending) throw EffekseerNativePINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public GraphicsDevice() : this(EffekseerNativePINVOKE.new_GraphicsDevice(), true) {
  }

}

}
