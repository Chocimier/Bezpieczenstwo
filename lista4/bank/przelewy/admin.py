from django.contrib import admin
from django.utils.safestring import mark_safe

from .models import Transfer, UnconfirmedTransfer
from .utils import confirm_transfer

def confirm_transfers(modeladmin, request, queryset):
    for t in queryset:
       confirm_transfer(t)

confirm_transfers.short_description = 'Zatwierdź'

admin.site.register(Transfer)

class UnconfirmedTransferAdmin(admin.ModelAdmin):
    actions = [confirm_transfers]
    # fields = ('title', 'image',)
    list_display = ('_get_title',)

    def _get_title(self, obj):
        return mark_safe(obj.title)

admin.site.register(UnconfirmedTransfer, UnconfirmedTransferAdmin)
