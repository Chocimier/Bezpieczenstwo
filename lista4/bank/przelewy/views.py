from django.contrib.auth.decorators import login_required
from django.http import HttpResponse, HttpResponseRedirect
from django.shortcuts import render
from django.urls import reverse
from .models import Transfer, UnconfirmedTransfer
from .utils import build_unconfirmed_transfer, build_transfer

def index(request):
    return render(request, 'transfers/index.html')

@login_required()
def transfers(request):
    out_transfers_list = Transfer.objects.filter(source = request.user.username)
    in_transfers_list = Transfer.objects.filter(target = request.user.username)
    return render(request, 'transfers/transfers.html', {'out_transfer_list': out_transfers_list, 'in_transfer_list': in_transfers_list})

@login_required()
def transfer_form(request):
    return render(request, 'transfers/transfer_form.html')

@login_required()
def transfer_form_target(request):
    transfer = build_unconfirmed_transfer(request)
    if transfer is None:
        return HttpResponseRedirect(reverse('transfer_form'))
    return HttpResponseRedirect(reverse('make_transfer', args=[transfer.id]))
 
@login_required()
def make_transfer(request, unconfirmed_id):
    try:
        transfer = UnconfirmedTransfer.objects.get(id=unconfirmed_id)
    except UnconfirmedTransfer.DoesNotExist:
        return HttpResponseRedirect(reverse('index'))
    if transfer.source != request.user.username:
        return HttpResponseRedirect(reverse('index'))
    return render(request, 'transfers/make_transfer.html', {'id': unconfirmed_id, 'source': transfer.source, 'target': transfer.target, 'amount': transfer.amount})
 
@login_required()
def make_transfer_target(request):
    transfer = build_transfer(request)
    if transfer is None:
        return HttpResponseRedirect(reverse('index'))
    return HttpResponseRedirect(reverse('transfer_details', args=[transfer.id]))
 
@login_required()
def transfer_details(request, id):
    try:
        transfer = Transfer.objects.get(id=id)
    except Transfer.DoesNotExist:
        return HttpResponseRedirect(reverse('index'))
    return render(request, 'transfers/transfer_details.html', {'source': transfer.source, 'target': transfer.target, 'amount': transfer.amount, 'date': transfer.created_date})
