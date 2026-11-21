#!/usr/bin/env python3
"""Generate a simple Yasumi app icon (SVG -> PNG)."""
import math

def draw_svg():
    s = []
    s.append('<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 1024 1024">')
    s.append('  <rect width="1024" height="1024" fill="#0B1220"/>')
    # Outer glow ring
    s.append('  <circle cx="512" cy="512" r="420" fill="none" stroke="#10B981" stroke-width="20" opacity="0.35"/>')
    s.append('  <circle cx="512" cy="512" r="380" fill="none" stroke="#10B981" stroke-width="12" opacity="0.5"/>')
    # Inner circle (card)
    s.append('  <circle cx="512" cy="512" r="300" fill="#10B981" opacity="0.95"/>')
    # Inner highlight
    s.append('  <circle cx="512" cy="512" r="280" fill="#065F46"/>')
    # Timer arc (a partial ring)
    s.append('  <circle cx="512" cy="512" r="230" fill="none" stroke="#FBBF24" stroke-width="18" stroke-dasharray="200 80" opacity="0.8"/>')
    # Time text
    s.append('  <text x="512" y="550" font-family="monospace" font-size="64" font-weight="bold" fill="#FBBF24" text-anchor="middle">5:00</text>')
    # Play/pause icon
    s.append('  <circle cx="512" cy="512" r="120" fill="#0B1220" opacity="0.6"/>')
    s.append('  <circle cx="512" cy="512" r="100" fill="#10B981"/>')
    s.append('  <path d="M512 412 L512 332 M512 612 L512 692 M412 512 L332 512 M612 512 L692 512" stroke="#0B1220" stroke-width="16" stroke-linecap="round" fill="none"/>')
    s.append('</svg>')
    return "\n".join(s)

if __name__ == "__main__":
    print(draw_svg())
