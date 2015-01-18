(function (window) {


var App = Ember.Application.create({

});

App.ApplicationAdapter = DS.FirebaseAdapter.extend({
	firebase: new Firebase('https://toilet-monitor.firebaseio.com')
});


App.Visit = DS.Model.extend({
	lightOn: DS.attr('boolean')
});

App.Visits = DS.Model.extend({
    lightOnAt: DS.attr('number'),
    lightOffAt: DS.attr('number'),
    duration: DS.attr('number')
});

App.Router.map(function(){
	this.resource('visit', {path: '/visit'});
	this.resource('visits', {path: '/visits'});
})

App.IndexRoute = Ember.Route.extend({
	redirect: function() {
		this.transitionTo('visits');
	}
});

App.VisitRoute = Ember.Route.extend({
	model: function() {
		console.log(this.store.find('visit'))
		return this.store.find('visit');
	}
});

App.VisitsRoute = Ember.Route.extend({
	model: function() {
		return this.store.find('visits');
	}
});

App.VisitsController = Ember.ArrayController.extend({
	sortAscending: true
}); 

})(window);